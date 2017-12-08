// pubsub.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <assert.h>
#include <string>
#include <iostream>
#include <nanomsg/nn.h>
#include <nanomsg/pubsub.h>
#include <time.h>
#include <windows.h>

std::string currentDate()
{
	time_t raw = time(&raw);
	struct tm info;
	localtime_s(&info, &raw);
	char text[256] = { 0 };
	asctime_s(text, &info);
	text[strlen(text) - 1] = '\0';
	return text;
}

int server(const std::string &url)
{
	int sock = nn_socket(AF_SP, NN_PUB);
	assert(sock >= 0);
	int err = nn_bind(sock, url.c_str());
	assert(err >= 0);
	while (1) {
		std::string date = currentDate();
		int bytes = nn_send(sock, date.c_str(), date.size() + 1, 0);
		std::cout << "send bytes:" << bytes << "," << date << std::endl;
		Sleep(1000);
	}
	return nn_shutdown(sock, 0);
}

int client(const std::string &url, const std::string &name)
{
	int sock = nn_socket(AF_SP, NN_SUB);
	assert(sock >= 0);
	int err = nn_setsockopt(sock, NN_SUB, NN_SUB_SUBSCRIBE, "", 0);
	assert(err >= 0);
	err = nn_connect(sock, url.c_str());
	assert(err >= 0);
	while (1) {
		char *buf = nullptr;
		int bytes = nn_recv(sock, &buf, NN_MSG, 0);
		assert(bytes >= 0);
		std::cout << "client name:" << name << ",msg:" << buf << std::endl;
		nn_freemsg(buf);
	}
	return nn_shutdown(sock, 0);
}

int _tmain(int argc, _TCHAR* argv[])
{
	std::string node = argc > 1 ? argv[1] : "";
	std::string url = argc > 2 ? argv[2] : "";
	std::string name = argc > 3 ? argv[3] : "";

	if (node == "server" && !url.empty()) {
		server(url);
	} else if (node == "client" && !url.empty() && !name.empty()) {
		client(url, name);
	} else {
		std::cerr << "Usage:pipeline server|client url [name]" << std::endl;
	}

	system("pause");
	return 0;
}

#if 0
启动服务端：pubsub.exe server ipc:///tmp/pubsub.ipc
启动客户端1：pubsub.exe client ipc:///tmp/pubsub.ipc client1
启动客户端2：pubsub.exe client ipc:///tmp/pubsub.ipc client2
#endif