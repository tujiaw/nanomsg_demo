// pipeline.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <assert.h>
#include <string>
#include <iostream>
#include <nanomsg/nn.h>
#include <nanomsg/pipeline.h>

void errlog(int no)
{
	if (no != 0) {
		std::cerr << nn_strerror(no) << std::endl;
	}
}

int node0(const std::string &url)
{
	int sock = nn_socket(AF_SP, NN_PULL);
	assert(sock >= 0);
	int resBind = nn_bind(sock, url.c_str());
	assert(resBind >= 0);
	while (1) {
		std::cout << "waiting recv msg" << std::endl;
		char *buf = nullptr;
		int bytes = nn_recv(sock, &buf, NN_MSG, 0);
		std::cout << "recv msg:" << buf << ", size:" << bytes << std::endl;
		nn_freemsg(buf);
	}
}

int node1(const std::string &url, const std::string &msg)
{
	int sock = nn_socket(AF_SP, NN_PUSH);
	int resConnect = nn_connect(sock, url.c_str());
	assert(resConnect >= 0);
	assert(sock >= 0);
	int bytes = nn_send(sock, msg.c_str(), msg.size() + 1, 0);
	assert(bytes == msg.size() + 1);
	return nn_shutdown(sock, 0);
}

int _tmain(int argc, _TCHAR* argv[])
{
	std::string node = argc > 1 ? argv[1] : "";
	std::string url = argc > 2 ? argv[2] : "";
	std::string msg = argc > 3 ? argv[3] : "";

	if (node == "node0" && !url.empty()) {
		node0(url);
	} else if (node == "node1" && !url.empty() && !msg.empty()) {
		node1(url, msg);
	} else {
		std::cerr << "Usage:pipeline node0|node1 url [msg]" << std::endl;
	}

	return 0;
}

#if 0
运行
启动接收端：pipeline node0 ipc:///tmp/reqrep.ipc
启动发送端：pipeline node1 ipc:///tmp/reqrep.ipc "helo,world"
#endif