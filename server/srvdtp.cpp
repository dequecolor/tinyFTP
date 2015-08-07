#include    "srvdtp.h"

void SrvDTP::init(SockStream & connSockStream)
{ 
	this->connSockStream = connSockStream;
	packet.init();
}
void SrvDTP::sendFile(const char *filename)
{
	int n;
	int sindex = 0;
	FILE* fp;	// Yo!
	char buf[MAXLINE];

	if ( (fp = fopen(filename, "rb")) == NULL)
	{
		// send Response
		packet.reset(HPACKET);
		snprintf(buf, MAXLINE, "%s", strerror(errno));
		packet.fill(0, INFO, strlen(buf), GET, 0, 0, buf);
		//packet.print();
		packet.htonp();
		connSockStream.Writen(packet.ps, PACKSIZE);
		return;
	} else {
		// send Response
		packet.reset(HPACKET);
		snprintf(buf, MAXLINE, "200 ok start to transfer");
		packet.fill(0, INFO, strlen(buf), GET, 0, 0, buf);
		packet.print();
		packet.htonp();
		connSockStream.Writen(packet.ps, PACKSIZE);
	}

	Error::msg("Sendfile now %s", filename);
	char body[PBODYCAP];
	while( (n = fread(body, sizeof(char), PBODYCAP, fp)) >0 )
	{
		packet.reset(HPACKET);
		packet.fill(0, DATA, n, GET, 0, ++sindex, body);
		//packet.print();
		packet.htonp();
		connSockStream.Writen(packet.ps, PACKSIZE);
		printf("file_block_length:%d\n",n);
	}

	// send EOT
	packet.reset(HPACKET);
	packet.fill(0, EOT, n, GET, 0, 0, NULL);
	packet.print();
	packet.htonp();
	connSockStream.Writen(packet.ps, PACKSIZE);
}
void SrvDTP::recvFile(FILE* f)
{
	// int x;
	// int i = 0, j = 0;
	// if((x = recv(sfd, data, size_packet, 0)) <= 0)
	// 	er("recv()", x);
	// j++;
	// hp = ntohp(data);
	// //printpacket(hp, HP);
	// while(hp->type == DATA)
	// {
	// 	i += fwrite(hp->buffer, 1, hp->datalen, f);
	// 	if((x = recv(sfd, data, size_packet, 0)) <= 0)
	// 		er("recv()", x);
	// 	j++;
	// 	hp = ntohp(data);
	// 	//printpacket(hp, HP);
	// }
	// fprintf(stderr, "\t%d data packet(s) received.\n", --j);	// j decremented because the last packet is EOT.
	// fprintf(stderr, "\t%d byte(s) written.\n", i);
	// if(hp->type == EOT)
	// 	return;
	// else
	// {
	// 	fprintf(stderr, "Error occured while downloading remote file.\n");
	// 	exit(2);
	// }
	// fflush(stderr);
}