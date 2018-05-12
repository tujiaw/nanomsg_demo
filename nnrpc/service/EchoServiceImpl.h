#ifndef NNRPC_ECHOSERVICEIMPL_H
#define NNRPC_ECHOSERVICEIMPL_H

#include "../proto/echo.pb.h"

class EchoServiceImpl : public echo::EchoService
{
public:
	EchoServiceImpl();
	~EchoServiceImpl();

	virtual void Echo1(::google::protobuf::RpcController* controller,
		const ::echo::EchoRequest* request,
		::echo::EchoResponse* response,
		::google::protobuf::Closure* done);
	virtual void Echo2(::google::protobuf::RpcController* controller,
		const ::echo::EchoRequest* request,
		::echo::EchoResponse* response,
		::google::protobuf::Closure* done);
};

#endif // NNRPC_ECHOSERVICEIMPL_H