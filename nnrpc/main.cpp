#include <iostream>
#include "RpcServer.h"
#include "./service/EchoServiceImpl.h"

#include "RpcChannel.h"
#include <sstream>

#if 0
int main(int argc, char *argv)
{
	std::cout << "--------server start--------" << std::endl;
	
	RpcServer server("tcp://127.0.0.1:4323");
	server.registerService(new EchoServiceImpl());
	server.start();

	getchar();
	return 0;
}

#else
int main(int argc, char *argv)
{
	std::cout << "--------client start--------" << std::endl;

	echo::EchoRequest request;
	echo::EchoResponse response;
	RpcChannel channel("tcp://127.0.0.1:4323");
	echo::EchoService::Stub stub(&channel);

	std::string msg("hello, world!");
	request.set_message(msg);
	stub.Echo1(nullptr, &request, &response, nullptr);
	std::cout << response.response() << std::endl;
	stub.Echo2(nullptr, &request, &response, nullptr);
	std::cout << response.response() << std::endl;

	getchar();
	return 0;
}
#endif