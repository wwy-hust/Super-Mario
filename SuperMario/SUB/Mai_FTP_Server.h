#ifndef Mai_FTP_Server_h
#define Mai_FTP_Server_h

#include "SUB/Mai_All.h"
#include "SUB/Heap_Alloc0.h"
#include "SUB/RandomAccessFile.h"
#include "SUB/MaiDir.h"
#include "SUB/MaiString.h"
#include "SUB/Unicode.h"
#include "SUB/Mai_TCP.h"

class Mai_FTP_Server_Trans_Func : public MaiThread
{
public:
#define MFSTFSTATUS_OK 0
#define MFSTFSTATUS_FINISHED 1
#define MFSTFSTATUS_ABORT -1
protected:
	Mai_I32 status;
public:
	virtual ~Mai_FTP_Server_Trans_Func() = 0;
	virtual Mai_Status abort() = 0;
	virtual Mai_Status getStatus() = 0;
};

class Mai_FTP_Server_Trans_Stor : public Mai_FTP_Server_Trans_Func
{
protected:
	Mai_TCP_Smp *mts0;
	RandomAccessFile *raf0;

	Mai_Quene0 *mq0;

	Mai_Bool is_running;

	Heap_Alloc0 heap0;
public:
	Mai_FTP_Server_Trans_Stor(Mai_TCP_Smp *mts0, Mai_I8 *path, Mai_I64 off);
	~Mai_FTP_Server_Trans_Stor();
	Mai_Status abort();
	Mai_Status Proc();
	Mai_Status getStatus();
};

class Mai_FTP_Server_Trans_Retr : public Mai_FTP_Server_Trans_Func
{
protected:
	Mai_TCP_Smp *mts0;
	RandomAccessFile *raf0;

	Mai_Quene0 *mq0;
	Mai_I64 offset;

	Mai_I64 filelen;

	Mai_Bool is_running;

	Heap_Alloc0 heap0;
public:
	Mai_FTP_Server_Trans_Retr(Mai_TCP_Smp *mts0, Mai_I8 *path, Mai_I64 off);
	~Mai_FTP_Server_Trans_Retr();
	Mai_Status abort();
	Mai_Status Proc();
	Mai_Status getStatus();
};

class Mai_FTP_Server_Trans_List : public Mai_FTP_Server_Trans_Func
{
protected:
	Mai_TCP_Smp *mts0;
	MaiDir *md0;

	Mai_Quene0 *mq0;

	Mai_Bool is_running;

	Mai_Bool is_file;
	Mai_Bool is_file_transed;

	Heap_Alloc0 heap0;
public:
	Mai_FTP_Server_Trans_List(Mai_TCP_Smp *mts0, Mai_I8 *path);
	~Mai_FTP_Server_Trans_List();
	Mai_Status abort();
	Mai_Status Proc();
	Mai_Status getStatus();
};

class Mai_FTP_Server_Commander : public MaiThread
{
protected:
	Mai_FTP_Server_Trans_Func *func_now;
	Mai_TCP_Smp *trans_conn_now;
protected:
	Mai_TCP_Server_Trans *mtst0;
	Mai_Quene0 *readbuf;
	Mai_Quene0 *writebuf;
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
private:
	Mai_Status makeFullPath(Mai_I8* rootp, Mai_I8* ftpp);
	Mai_Status makePath(Mai_I8* dst, Mai_I8* src0, Mai_I8* src1);
public:
	Mai_Status writeCommand(Mai_I8* command);
public:
	Mai_FTP_Server_Commander(Mai_TCP_Server_Trans *mtst0);
	~Mai_FTP_Server_Commander();
	Mai_Status shutdown();
	virtual Mai_Status deletePre();
	Mai_Status Proc();
};

class Mai_FTP_Server : public Mai_TCP_Server
{
public:
	Mai_FTP_Server(Mai_I32 port);
	Mai_Status doACP(Mai_TCP_Server_Trans *mtst0);
};

#endif
