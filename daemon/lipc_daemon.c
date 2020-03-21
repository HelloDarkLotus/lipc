#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/un.h>
#include "lipc_session.h"

static int32_t lipc_daemon_init(int32_t * fp)
{
	int32_t handle = socket(AF_UNIX, SOCK_STREAM, 0);
	if (handle < 0)
	{
		return -1;
	}

	unlink("/var/session");

	struct sockaddr_un addr;
	addr.sun_family = AF_UNIX;
	strcpy(addr.sun_path, "/var/session");

	if (bind(handle, (struct sockaddr*) & addr, sizeof(addr)) < 0)
	{
		close(handle);
		return -1;
	}

	listen(handle, 50);

	*fp = handle;

	return 0;
}

void* recv_data_proc(void* arg)
{
	int32_t handle = *(int32_t*)arg;

	while (1)
	{
		char buff[2048] = { 0 };
		int32_t len = lipc_session_recv(handle, buff, 2048);
		if (len > 0)
		{
			printf("recv data [%s] from [%d]\n", buff, handle);
		}

		//sleep(1);
	}
}

int32_t main(int32_t argc, char* argv[])
{
	int32_t daemon_handle = -1;

	int32_t ret = lipc_daemon_init(&daemon_handle);
	if (ret < 0)
	{
		return -1;
	}

	while (1)
	{
		int32_t conn_fd = accept(daemon_handle, NULL, NULL);
		if (conn_fd > 0)
		{
			pthread_t pid;
			pthread_create(&pid, NULL, recv_data_proc, (void *)&conn_fd);
		}
		else
		{
			sleep(1);
		}
	}

	return 0;
}
