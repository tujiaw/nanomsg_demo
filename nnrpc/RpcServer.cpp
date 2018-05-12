#include "RpcServer.h"
#include <nanomsg/reqrep.h>
#include "util.h"

RpcServer::RpcServer(const std::string &url)
	: sock_(AF_SP, NN_REP)
	, sockid_(sock_.bind(url))
{
}


RpcServer::~RpcServer()
{
	removeService();
	close();
}

void RpcServer::endpoint(const std::string &url)
{
	sock_.bind(url);
}

void RpcServer::registerService(protobuf::Service *service)
{
	const protobuf::ServiceDescriptor *desc = service->GetDescriptor();
	for (int i = 0; i < desc->method_count(); i++) {
		const protobuf::MethodDescriptor *methodDesc = desc->method(i);
		const protobuf::Message *request = &service->GetRequestPrototype(methodDesc);
		const protobuf::Message *response = &service->GetResponsePrototype(methodDesc);
		RpcMethod *method = new RpcMethod(service, request, response, methodDesc);
		const std::string &name = methodDesc->full_name();
		uint64_t hashCode = util::strhash(name);
		auto iter = methodMap_.find(hashCode);
		if (iter == methodMap_.end()) {
			methodMap_[hashCode] = method;
		}
	}
}

void RpcServer::removeService()
{
	for (auto iter = methodMap_.begin(); iter != methodMap_.end(); ) {
		RpcMethod *method = iter->second;
		++iter;
		delete method;
	}
}

void RpcServer::start()
{
	uint64_t hashCode = 0;
	while (1) {
		char *buf = nullptr;
		int bytes = sock_.recv(&buf, NN_MSG, 0);
		if (bytes <= 0) {
			continue;
		}
		memcpy((char*)&hashCode, buf, sizeof(hashCode));
		auto iter = methodMap_.find(hashCode);
		if (iter == methodMap_.end()) {
			continue;
		}
		RpcMethod *method = iter->second;
		protobuf::Message *request = method->request_->New();
		protobuf::Message *response = method->response_->New();
		request->ParseFromString(buf + sizeof(hashCode));
		freemsg(buf);
		method->service_->CallMethod(method->method_, nullptr, request, response, nullptr);
		size_t msgLen = response->ByteSize();
		buf = (char*)allocmsg(msgLen, 0);
		response->SerializeToArray(buf, msgLen);
		sock_.send(buf, msgLen, 0);
		delete request;
		delete response;
		freemsg(buf);
	}
}

void RpcServer::close()
{
	if (sockid_ > 0) {
		sock_.shutdown(0);
		sockid_ = 0;
	}
}