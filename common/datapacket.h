#ifndef _TINYFTP_DATAPACKET_H_
#define _TINYFTP_DATAPACKET_H_

#include    "common.h"
#include    "error.h"


class DataPacket
{
public:

	DataPacket(PacketStoreType pstype)
	{ 
		this->pstype = pstype;
		zero(&dpack);  
	};	
	void init(uint32_t sesid, uint16_t nslice, uint16_t sindex, uint16_t bsize, char body[CBODYCAP])
	{ 
		
		dpack.sesid = sesid;
		dpack.nslice = nslice;
		dpack.sindex = sindex;
		dpack.bsize  = bsize;
		memcpy(dpack.body, body, DBODYCAP);   
	};

	void zero(DPacket* p);

	DPacket* ntohp(DPacket* np);

	DPacket* htonp(DPacket* hp);

	void print();


//private:
	DPacket	dpack;
	PacketStoreType pstype;

};

#endif /* _TINYFTP_DPACKET_H_ */