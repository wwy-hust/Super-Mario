#ifndef MaiSocket_h
#define MaiSocket_h

#include "SUB/Mai_All.h"
#include "SUB/Mai_mem.h"

class MaiSocket
{
private:
	volatile struct
	{
		Mai_I32 h_handle;
	} infos;
public:
	MaiSocket(Mai_I32 h_handle = -1, Mai_Bool tcp_or_udp = 0);
	Mai_Status bind(Mai_I32 port);
	Mai_Status listen(Mai_I32 queues);
	Mai_Status connect(Mai_I32 ip, Mai_I32 port);
	Mai_Status connect(Mai_I8 *host, Mai_I32 port);
	MaiSocket *accept(Mai_I32 timeout_minisec = 0);
	Mai_Status recv(Mai_I8 *buf, Mai_I32 buf_size, Mai_I32 *recved, Mai_I32 timeout_minisec = 0);
	Mai_Status send(Mai_I8 *buf, Mai_I32 buf_size, Mai_I32 *sent, Mai_I32 timeout_minisec = 0);
	Mai_Status shutdownWriting();
	Mai_Status close();
	Mai_U32 getThisIP();
};

#endif
