#ifndef _TINYFTP_CLIPI_H_
#define _TINYFTP_CLIPI_H_

#include    "../common/common.h"
#include    "../common/error.h"
#include    "../common/packet.h"
#include    "../common/sockstream.h"

// Server Data Transfer Process (SrvDTP)
class SrvDTP
{
public:
	void init(SockStream & connSockStream);
	void sendFile(const char *filename);
	void recvFile(FILE* f);


private:
	Packet packet;
	SockStream connSockStream;

};

#endif /* _TINYFTP_CLIPI_H_ */