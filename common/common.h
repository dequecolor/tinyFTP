/* common header.  Tabs are set for 4 spaces, not 8 */

#ifndef _TINYFTP_COMMON_H_
#define _TINYFTP_COMMON_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>     // sockaddr_in{} and other Internet definitions
#include <arpa/inet.h>      // inet(3) functions
#include <netdb.h>

#include <cstdio>
#include <cstdlib>

// #include <stdio.h>
// #include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

// c++ header
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

// using std::map;
// using std::string;
// using std::iostream;

#define DEBUG 1

// MACRO constants
#define	LISTENQ		1024		// 2nd argument(backlog) to listen()

// Miscellaneous constants
#define	MAXLINE		128			// max text line length
#define	BUFFSIZE	8192		// 8K Bytes buffer size for reads and writes

//#define PORT		2121		// server: listening port
#define CTRPORT		2121    	// server: control listening port
#define DATPORT		2020		// server: data pistening port

// Following shortens all the typecasts of pointer arguments
#define	SA	struct sockaddr

typedef enum sockType
{
	SRV_SOCKET,					// server socket tyoe
	CLI_SOCKET					// client socket type
} SockType;

/*********************************************************
 ******************* packet ******************************
 *********************************************************/
typedef enum packetStoreType
{
	HPACKET,					// Host storage type
	NPACKET						// Network storage type
} PacketStoreType;

// typedef enum packetType
// {
// 	CTRPACKET,					// control packet type
// 	DATPCKET					// data packet type
// } PacketType;

/************************** CtrPacket **********************************/

#define CHEADSIZE		8			// control packet header size
#define	CBODYCAP		120			// control packet body capcacity

// TCP control packet definition, communication protocol
 #pragma pack(4)
typedef struct cPacket
{
	/* control packet header */
	uint32_t sesid;			// Session id
	uint16_t cmdid;			// Command ID
	uint16_t bsize;			// Data: the real size of body 

	/* control packet body */
	char body[CBODYCAP];	// control packet body
	
} CPacket;

#define CPACKSIZE sizeof(CPacket)

// different file transfer control commands

typedef enum cmdID
{
	USER = 1,
	PASS,
	GET,
	PUT,
	MGET,
	MPUT,
	DELE,
	RGET,
	RPUT,
	CD,
	LS,
	MKD,
	PWD,
	RMD,
	BINARY,
	ASCII,
	QUIT,

	INFO,
	EOT
} CmdID;



/************************** DatPacket **********************************/
#define DHEADSIZE		10			// data packet header size
#define	DBODYCAP		1024		// data packet body capcacity, basic file slice size

// TCP data packet definition, data transfer protocol
 #pragma pack(4)
typedef struct dPacket
{
	/* data packet header */
	uint32_t sesid;			// Session id
	uint16_t nslice;		// Data: whole number of file slices
	uint16_t sindex;		// Data: slice index
	uint16_t bsize;			// Data: the real size of body 

	/* data packet body */
	char body[DBODYCAP];	// packet body
	
} DPacket;

#define DPACKSIZE sizeof(DPacket)


/*********************************************************
 ******************* functions ***************************
 *********************************************************/

void Fclose(FILE *fp);
FILE * Fdopen(int fd, const char *type);
char * Fgets(char *ptr, int n, FILE *stream);
FILE * Fopen(const char *filename, const char *mode);
void Fputs(const char *ptr, FILE *stream);
void * Malloc(size_t size);


#endif	/* __TINYFTP_COMMON_H__ */