#include "EchoServiceImpl.h"
#include <iostream>

EchoServiceImpl::EchoServiceImpl()
{

}

EchoServiceImpl::~EchoServiceImpl()
{

}

void EchoServiceImpl::Echo1(::google::protobuf::RpcController* controller,
	const ::echo::EchoRequest* request,
	::echo::EchoResponse* response,
	::google::protobuf::Closure* done)
{
	std::cout << "echo1:" << request->message() << std::endl;
	response->set_response(std::string("echo1 response:") + request->message());
	if (done) {
		done->Run();
	}
}

void EchoServiceImpl::Echo2(::google::protobuf::RpcController* controller,
	const ::echo::EchoRequest* request,
	::echo::EchoResponse* response,
	::google::protobuf::Closure* done)
{
	std::cout << "echo2:" << request->message() << std::endl;
	response->set_response(std::string("echo2 response:") + request->message());
	if (done) {
		done->Run();
	}
}
