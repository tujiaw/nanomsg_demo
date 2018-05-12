#ifndef NNRPC_RCPSERVER_H
#define NNRPC_RCPSERVER_H

#include <unordered_map>
#include "RpcMethod.h"
#include "Socket.h"

class RpcServer
{
public:
	typedef std::unordered_map<uint64_t, RpcMethod*> RpcMethodMap;
	explicit RpcServer(const std::string &url);
	~RpcServer();

	void endpoint(const std::string &url);
	void registerService(protobuf::Service *service);
	void removeService();
	void start();
	void close();

private:
	Socket sock_;
	int sockid_;
	RpcMethodMap methodMap_;
};

#endif // NNRPC_RCPSERVER_H