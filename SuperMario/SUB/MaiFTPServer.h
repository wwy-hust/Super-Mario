#ifndef MaiFTPServer_h
#define MaiFTPServer_h

#include "SUB/Mai_All.h"
#include "SUB/MaiThread.h"
#include "SUB/Heap_Alloc0.h"
#include "SUB/RandomAccessFile.h"
#include "SUB/MaiDir.h"
#include "SUB/MaiString.h"
#include "SUB/Unicode.h"
#include "SUB/MaiSocket.h"

class MaiFTPServerTransFunc : public MaiThread
{
public:
#define MFSTFSTATUS_OK 0
#define MFSTFSTATUS_FINISHED 1
#define MFSTFSTATUS_ABORT -1
protected:
	Mai_I32 status;
public:
	virtual ~MaiFTPServerTransFunc() = 0;
	virtual Mai_Status abort() = 0;
	virtual Mai_Status getStatus() = 0;
};

class MaiFTPServerTransStor : public MaiFTPServerTransFunc
{
protected:
	MaiSocket *mts0;
	RandomAccessFile *raf0;

	Mai_Bool is_running;

	Heap_Alloc0 heap0;
public:
	MaiFTPServerTransStor(MaiSocket *mts0, Mai_I8 *path, Mai_I64 off);
	~MaiFTPServerTransStor();
	Mai_Status abort();
	Mai_Status Proc();
	Mai_Status getStatus();
};

class MaiFTPServerTransRetr : public MaiFTPServerTransFunc
{
protected:
	MaiSocket *mts0;
	RandomAccessFile *raf0;

	Mai_I64 offset;

	Mai_I64 filelen;

	Mai_Bool is_running;

	Heap_Alloc0 heap0;
public:
	MaiFTPServerTransRetr(MaiSocket *mts0, Mai_I8 *path, Mai_I64 off);
	~MaiFTPServerTransRetr();
	Mai_Status abort();
	Mai_Status Proc();
	Mai_Status getStatus();
};

class MaiFTPServerTransList : public MaiFTPServerTransFunc
{
protected:
	//Mai_TCP_Smp *mts0;
	MaiSocket *mts0;
	MaiDir *md0;

	//Mai_Quene0 *mq0;

	Mai_Bool is_running;

	Mai_Bool is_file;
	Mai_Bool is_file_transed;

	Heap_Alloc0 heap0;
public:
	MaiFTPServerTransList(MaiSocket *mts0, Mai_I8 *path);
	~MaiFTPServerTransList();
	Mai_Status abort();
	Mai_Status Proc();
	Mai_Status getStatus();
};

class MaiFTPServerCommander : public MaiThread
{
#define MFSCSTATUS_OK 0
#define MFSCSTATUS_CLOSED -1
protected:
	MaiFTPServerTransFunc *func_now;
	MaiSocket *trans_conn_now;
protected:
	MaiSocket *mtst0;
	//Mai_Quene0 *readbuf;
	//Mai_Quene0 *writebuf;
	Heap_Alloc0 heap0;
protected:
	Mai_I8 *rootpath;
	Mai_I8 *ftppath;
	Mai_I8 *fullpath;

	Mai_I8 *renamebuf;

	Mai_I64 rest_off;

	Mai_Bool is_running;

	Mai_I32 pasv_port_min;
	Mai_I32 pasv_port_max;

	Mai_Bool is_pasv;
	Mai_I8 portip[0x40];
	Mai_I32 portport;

	Mai_Status status;
private:
	Mai_Status makeFullPath(Mai_I8* rootp, Mai_I8* ftpp);
	Mai_Status makePath(Mai_I8* dst, Mai_I8* src0, Mai_I8* src1);
public:
	Mai_Status writeCommand(Mai_I8* command);
public:
	MaiFTPServerCommander(MaiSocket *mtst0);
	~MaiFTPServerCommander();
	Mai_Status shutdown();
	virtual Mai_Status deletePre();
	Mai_Status Proc();
};

class MaiFTPServer : public MaiThread
{
private:
	MaiSocket *mainsoc0;
public:
	MaiFTPServer(Mai_I32 port);
	Mai_Status Proc();
};

#endif
