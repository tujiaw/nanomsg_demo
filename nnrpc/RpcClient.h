#ifndef NNRPC_RPCCLIENT_H
#define NNRPC_RPCCLIENT_H

#include "RpcChannel.h"

class RpcClient
{
public:
	RpcClient(const std::string &url);
	~RpcClient();

private:
	RpcChannel channel_;
};

#endif // NNRPC_RPCCLIENT_H