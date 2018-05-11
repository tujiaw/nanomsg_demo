#ifndef NNRPC_SOCKET_H
#define NNRPC_SOCKET_H

#include <nanomsg/nn.h>
#include <cstdint>
#include <cassert>
#include <string>

inline const char* symbol(int i, int *value)
{
	return nn_symbol(i, value);
}

inline void* allocmsg(size_t size, int type)
{
	return nn_allocmsg(size, type);
}

inline int freemsg(void *msg)
{
	return nn_freemsg(msg);
}

inline void term()
{
	nn_term();
}

class Socket
{
public:
	Socket(int domain, int protocol)
		: s_(nn_socket(domain, protocol))
	{
	}

	~Socket()
	{
		int ret = nn_close(s_);
		assert(ret == 0);
	}

	void setsockopt(int level, int option, const void *optval, size_t optvallen)
	{
		int ret = nn_setsockopt(s_, level, option, optval, optvallen);
		assert(ret == 0);
	}

	void getsockopt(int level, int option, void *optval, size_t *optvallen)
	{
		int ret = nn_getsockopt(s_, level, option, optval, optvallen);
		assert(ret == 0);
	}

	int bind(const std::string &addr)
	{
		int ret = nn_bind(s_, addr.c_str());
		assert(ret >= 0);
		return ret;
	}

	int connect(const std::string &addr)
	{
		int ret = nn_connect(s_, addr.c_str());
		assert(ret >= 0);
		return ret;
	}

	void shutdown(int how)
	{
		int ret = nn_shutdown(s_, how);
		assert(ret == 0);
	}

	int send(const void* buf, size_t len, int flags)
	{
		int ret = nn_send(s_, buf, len, flags);
		assert(nn_errno() == EAGAIN);
		return ret;
	}

	int rect(void *buf, size_t len, int flags)
	{
		int ret = nn_recv(s_, buf, len, flags);
		assert(nn_errno() == EAGAIN);
		return ret;
	}

	int sendmsg(const struct nn_msghdr *msg, int flags)
	{
		int ret = nn_sendmsg(s_, msg, flags);
		assert(nn_errno() == EAGAIN);
		return ret;
	}

	int recvmsg(struct nn_msghdr *msg, int flags)
	{
		int ret = nn_recvmsg(s_, msg, flags);
		assert(nn_errno() == EAGAIN);
		return ret;
	}

private:
	Socket(const Socket&);
	void operator=(const Socket&);

private:
	int s_;
};

#endif // NNRPC_SOCKET_H