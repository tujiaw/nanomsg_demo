#ifndef NNRPC_RCPCHANNEL_H
#define NNRPC_RCPCHANNEL_H

#include <google/protobuf/service.h>
#include <google/protobuf/message.h>
#include <nanomsg/nn.h>
#include <string>
#include "Socket.h"

using namespace google;
class RpcChannel : public protobuf::RpcChannel
{
public:
	RpcChannel(const std::string &url);
	virtual ~RpcChannel();
	virtual void CallMethod(const protobuf::MethodDescriptor* method,
		protobuf::RpcController* controller,
		const protobuf::Message* request,
		protobuf::Message* response,
		protobuf::Closure* done);

private:
	Socket sock_;
	int sockid_;
};

#endif // NNRPC_RCPCHANNEL_H