#ifndef _LIPC_SESSION_H_
#define _LIPC_SESSION_H_

#include <stdint.h>

int32_t lipc_session_init(int32_t* p_session);

void lipc_session_close(int32_t session);

void lipc_session_create(int32_t session);

int32_t lipc_session_recv(int32_t session, void * buff, uint32_t expected_recv_len);

int32_t lipc_session_send(int32_t session, const void * buff, uint32_t buff_len);

#endif
