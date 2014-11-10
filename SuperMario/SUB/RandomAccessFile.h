#ifndef RandomAccessFile_h
#define RandomAccessFile_h

#include "SUB/Mai_All.h"
#include "SUB/Heap_Alloc0.h"
#include "SUB/MaiString.h"
#include "SUB/Unicode.h"

/* RandomAccessFile */
class RandomAccessFile
{
public:
	RandomAccessFile(Mai_I8* src, Mai_I8* s);
	RandomAccessFile(Mai_WChar* src, Mai_WChar* s);
	~RandomAccessFile();
	Mai_Status open();
	Mai_Status close();
	Mai_Bool is_exist();
	Mai_Status del();
	Mai_Status moveTo(Mai_I8* dst);
	Mai_Status moveTo(Mai_WChar* dst);
	Mai_Status seek(Mai_I64 pos);
	Mai_I64 getFilePointer();
	Mai_I64 length();
	Mai_I32 skipBytes(Mai_I32 n);
	Mai_Status setLength(Mai_I64 newLength);
	Mai_I32 read(Mai_Void* b, Mai_I32 off, Mai_I32 len);
	Mai_I32 write(Mai_Void* b, Mai_I32 off, Mai_I32 len);
	Mai_I8 readI8();
	Mai_Status writeI8(Mai_I8 data);
	Mai_I16 readI16();
	Mai_Status writeI16(Mai_I16 data);
	Mai_I16 readI16Big();
	Mai_Status writeI16Big(Mai_I16 data);
	Mai_I32 readI32();
	Mai_Status writeI32(Mai_I32 data);
	Mai_I32 readI32Big();
	Mai_Status writeI32Big(Mai_I32 data);
	Mai_I64 readI64();
	Mai_Status writeI64(Mai_I64 data);
	Mai_I64 readI64Big();
	Mai_Status writeI64Big(Mai_I64 data);
private:
#ifdef MAI_WIN
	Mai_Status init(Mai_WChar* src, Mai_WChar* s);
#else
	Mai_Status init(Mai_I8* src, Mai_I8* s);
#endif
private:
#ifdef MAI_WIN
	WCHAR* src;
	HANDLE file0;
	Mai_I32 method;
	Mai_I32 share_mode;
	Mai_I32 creation;
	Heap_Alloc0 heap0;
#else
	Mai_I8* src;
	FILE* file0;
	Mai_I32 method;
	Mai_I32 share_mode;
	Mai_I32 creation;
	Heap_Alloc0 heap0;
#endif
};

#endif
