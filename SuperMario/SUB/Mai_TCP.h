#ifndef Mai_TCP_h
#define Mai_TCP_h

#include "SUB/Mai_All.h"
#include "SUB/Heap_Alloc0.h"
#include "SUB/MaiThread.h"
#include "SUB/Mai_Quene0.h"

/* Mai_TCP_Smp */
class Mai_TCP_Smp : public MaiThread
{
public:
#define MTSSSTATUS_OK 0
#define MTSSSTATUS_RECV_CLOSED -1
#define MTSSSTATUS_RECV_FAILED -2
#define MTSSSTATUS_SEND_FAILED -3
#define MTSSSTATUS_CLOSE -4
#define MTSSSTATUS_CLOSED -99
public:
	virtual ~Mai_TCP_Smp() = 0;
	virtual Mai_Status closeC() = 0;
	virtual Mai_Quene0* getReadQuene() = 0;
	virtual Mai_Quene0* getWriteQuene() = 0;
	virtual Mai_Status getStatus() = 0;
	virtual Mai_Bool isTransferFinished() = 0;
};

/* Mai_TCP_Server_Smp */
class Mai_TCP_Server_Smp : public Mai_TCP_Smp
{
public:
#define MTSSSTATUS_BIND_ERROR -5
#define MTSSSTATUS_LISTEN_ERROR -6

	class sThread : public MaiThread
	{
	private:
		Mai_TCP_Server_Smp* mtss0;
	public:
		sThread(Mai_TCP_Server_Smp* mtss);
		Mai_Status Proc();
	};

protected:
	Mai_Status status;

	Mai_Bool is_proc1;
	Mai_Bool is_proc2;

	Mai_Bool is_transfer_finished;

	Mai_I32 port;
protected:
	Mai_I32 ConnectSocket;
	sThread *sthread;
protected:
	Heap_Alloc0 heap0;
	Mai_Quene0* read_buffer;
	Mai_Quene0* write_buffer;
	Mai_I32 r_buf_size;
	Mai_I32 w_buf_size;
public:
	Mai_TCP_Server_Smp(Mai_I32 port);
	~Mai_TCP_Server_Smp();
	virtual Mai_Status doACP();
	Mai_Status Proc();
	Mai_Status Proc2();
	virtual Mai_Status ErrorR();
	Mai_Status closeC();
	Mai_Quene0* getReadQuene();
	Mai_Quene0* getWriteQuene();
	Mai_Status getStatus();
	Mai_Bool isTransferFinished();
};

/* Mai_TCP_Server_Trans */
class Mai_TCP_Server_Trans : public MaiThread
{
public:
#define MTSTSTATUS_OK 0
#define MTSTSTATUS_RECV_CLOSED -1
#define MTSTSTATUS_RECV_FAILED -2
#define MTSTSTATUS_SEND_FAILED -3
#define MTSTSTATUS_CLOSE -4
#define MTSTSTATUS_CLOSED -99
	class sThread : public MaiThread
	{
	private:
		Mai_TCP_Server_Trans* mtst0;
	public:
		sThread(Mai_TCP_Server_Trans* mtst);
		Mai_Status Proc();
	};
	
protected:
	Mai_Status status;

	Mai_Bool is_proc1;
	Mai_Bool is_proc2;

	Mai_Bool is_transfer_finished;
	
protected:
	Mai_I32 TransSocket;
	sThread *sthread;

	Mai_U32 thisip;
	
protected:
	Heap_Alloc0 heap0;
	Mai_Quene0* read_buffer;
	Mai_Quene0* write_buffer;
	
	Mai_I32 r_buf_size;
	Mai_I32 w_buf_size;
	
public:
	Mai_TCP_Server_Trans(Mai_I32 TransSocket);
	~Mai_TCP_Server_Trans();
	Mai_Status Proc();
	Mai_Status Proc2();
	virtual Mai_Status ErrorR();
	Mai_Status closeC();
	Mai_Quene0* getReadQuene();
	Mai_Quene0* getWriteQuene();
	Mai_Status getStatus();
	Mai_U32 getThisIP();
	Mai_Bool isTransferFinished();
};

/* Mai_TCP_Server */
class Mai_TCP_Server : public MaiThread
{
public:
#define MTSSTATUS_OK 0
#define MTSSTATUS_BIND_ERROR -1
#define MTSSTATUS_LISTEN_ERROR -2
#define MTSSTATUS_CLOSE -2
#define MTSSTATUS_CLOSED -99

protected:
	Mai_Status status;
	
	Mai_Bool is_accepting;

	Mai_I32 port;
protected:
	Mai_I32 ConnectSocket;

protected:
	Heap_Alloc0 heap0;

public:
	Mai_TCP_Server(Mai_I32 port);
	~Mai_TCP_Server();
	virtual Mai_Status doACP(Mai_TCP_Server_Trans *mtst0);
	Mai_Status Proc();
	virtual Mai_Status ErrorR();
	Mai_Status closeC();
	Mai_Status getStatus();
};

/* Mai_TCP_Client */
class Mai_TCP_Client : public Mai_TCP_Smp
{
public:
#define MTSSSTATUS_CONNECT_ERROR -50

	class sThread : public MaiThread
	{
	private:
		Mai_TCP_Client* mtc0;
	public:
		sThread(Mai_TCP_Client* mtc);
		Mai_Status Proc();
	};

protected:
	Mai_Status status;

	Mai_Bool is_proc1;
	Mai_Bool is_proc2;

	Mai_Bool is_transfer_finished;

protected:
	Mai_I32 ConnectSocket;
	//struct addrinfo *ai;
	sThread *sthread;
protected:
	Heap_Alloc0 heap0;
	Mai_Quene0* read_buffer;
	Mai_Quene0* write_buffer;
	Mai_I32 r_buf_size;
	Mai_I32 w_buf_size;
public:
	Mai_TCP_Client(Mai_I8* host, Mai_I32 port);
	~Mai_TCP_Client();
	Mai_Status Proc();
	Mai_Status Proc2();
	virtual Mai_Status ErrorR();
	Mai_Status closeC();
	Mai_Quene0* getReadQuene();
	Mai_Quene0* getWriteQuene();
	Mai_Status getStatus();
	Mai_Bool isTransferFinished();
};

#endif
