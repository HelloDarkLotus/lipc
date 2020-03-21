#include <assert.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include "lipc_session.h"

int32_t lipc_session_init(int32_t* p_session)
{
	assert(NULL != p_session);

	int32_t handle = socket(AF_UNIX, SOCK_STREAM, 0);
	if (handle < 0)
	{
		return -1;
	}

	*p_session = handle;

	return 0;
}

void lipc_session_close(int32_t session)
{
	close(session);
}

void lipc_session_create(int32_t session)
{
	struct sockaddr_un addr;
	addr.sun_family = AF_UNIX;
	strcpy(addr.sun_path, "/var/session");

	while (connect(session, (struct sockaddr*) & addr, sizeof(addr)) != 0)
	{
		sleep(1);
	}
}

int32_t lipc_session_recv(int32_t session, void* buff, uint32_t expected_recv_len)
{
	assert(NULL != buff);

	return recv(session, buff, expected_recv_len, 0);
}

int32_t lipc_session_send(int32_t session, const void* buff, uint32_t buff_len)
{
	assert(NULL != buff);

	return send(session, buff, buff_len, 0);
}
