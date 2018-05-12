#ifndef NNRPC_RPCMETHOD_H
#define NNRPC_RPCMETHOD_H

#include <google/protobuf/service.h>
#include <google/protobuf/message.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/stubs/common.h>

using namespace google;
struct RpcMethod {
public:
	RpcMethod(protobuf::Service *service,
		const protobuf::Message *request,
		const protobuf::Message *response,
		const protobuf::MethodDescriptor *method)
		: service_(service)
		, request_(request)
		, response_(response)
		, method_(method) {
	}

	protobuf::Service *service_;
	const protobuf::Message *request_;
	const protobuf::Message *response_;
	const protobuf::MethodDescriptor *method_;

private:
	RpcMethod(const RpcMethod&);
	void operator=(const RpcMethod&);
};

#endif // NNRPC_RPCMETHOD_H