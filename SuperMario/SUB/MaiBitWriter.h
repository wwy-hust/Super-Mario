#ifndef MaiBitWriter_h
#define MaiBitWriter_h

#include "SUB/Mai_All.h"
#include "SUB/MaiCriticalSection.h"
#include "SUB/Mai_Quene0.h"

#define MaiBitWriterTypeHigh 0
#define MaiBitWriterTypeLow 1

class MaiBitWriter
{
private:
	Mai_Quene0* quene_out;
	Mai_I32 buffer;
	Mai_I32 bits_num;
	Mai_I32 type;

	MaiCriticalSection mcs0;
private:
	Mai_Status putByte();
public:
	MaiBitWriter(Mai_I32 byte_buf_size, Mai_I32 type = MaiBitWriterTypeHigh);
	~MaiBitWriter();
	Mai_I32 getData(Mai_I8* dst, Mai_I32 len_to_get);
	Mai_Status putWithI32Buffer(Mai_I32 src, Mai_I32 bnum);
	Mai_Status flush();
};

#endif
