#include "lipc_session.h"
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

int32_t main(int32_t argc, char * argv[])
{
	int32_t handle = -1;

	if (lipc_session_init(&handle) < 0)
	{
		printf("session init failed.\n");
		return -1;
	}

	lipc_session_create(handle);

	while (1)
	{
		int32_t ret = lipc_session_send(handle, "Welcome to WUHAN", 17);
		sleep(1);
	}

	return 0;
}
