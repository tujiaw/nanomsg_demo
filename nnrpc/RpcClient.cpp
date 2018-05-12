#include "RpcClient.h"


RpcClient::RpcClient(const std::string &url)
	: channel_(url)
{
}


RpcClient::~RpcClient()
{
}
