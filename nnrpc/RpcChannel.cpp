#include "RpcChannel.h"
#include <google/protobuf/descriptor.h>
#include <nanomsg/reqrep.h>

RpcChannel::RpcChannel(const std::string &url)
	: sock_(AF_SP, NN_REQ)
	, sockid_(sock_.connect(url))
{
}

RpcChannel::~RpcChannel()
{
	if (sockid_ > 0) {
		sock_.shutdown(0);
		sockid_ = 0;
	}
}

void RpcChannel::CallMethod(const protobuf::MethodDescriptor* method,
	protobuf::RpcController* controller,
	const protobuf::Message* request,
	protobuf::Message* response,
	protobuf::Closure* done)
{
	const std::string &name = method->full_name();

}