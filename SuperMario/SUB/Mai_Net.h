
/*class Mai_TCP_Server : public MaiThread
{
public:
	class sThread : public MaiThread
	{
	private:
		Mai_TCP_Server* mts0;
	public:
		sThread(Mai_TCP_Server* mts);
		Mai_Status Proc();
	};
public:
	typedef struct _Per_Handle_Data
	{
		SOCKET shandle;
		sockaddr_in addr;
		Mai_I8 buffer[1024 * 16];
	} Per_Handle_Data;

	typedef struct _Per_IO_Data
	{
#define RBUFFER_SIZE 1024*1024
#define WBUFFER_SIZE 1024*1024

		OVERLAPPED ol;
		Mai_I8 rbuf[RBUFFER_SIZE];
		Mai_I32 r_received;
		Mai_I32 r_recved_total;
		//Mai_I8 wbuf[WBUFFER_SIZE];
		Mai_I32 nOperationType;

		DWORD dwFlags;

#define OP_READ   1
#define OP_WRITE 2
#define OP_ACCEPT 3

	} Per_IO_Data;

protected:
	HANDLE hiocp;
	SOCKET lsocket;
	sThread *sthread;
	Heap_Alloc0 heap0;
	//friend class sThread;
public:
	Mai_TCP_Server(Mai_I32 port);
	Mai_Status Proc();
	virtual Mai_Status doACP(Per_Handle_Data *phd);
	Mai_Status Proc2();
	virtual Mai_Status readProc(Per_Handle_Data* phd, Per_IO_Data* pid, DWORD dwTrans);
	virtual Mai_Status doclose(Per_Handle_Data* phd, Per_IO_Data* pid);
	
};*/


/*class Mai_TCP_Client : public MaiThread
{
public:
#define TCSTATUS_RECV_CLOSED -1
#define TCSTATUS_RECV_FAILED -2
#define TCSTATUS_SEND_FAILED -3
#define TCSTATUS_CLOSE -4
#define TCSTATUS_CLOSED -99

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
protected:
	SOCKET ConnectSocket;
	struct addrinfo *ai;
	sThread *sthread;
protected:
	Heap_Alloc0 heap0;
	Mai_Quene0* read_buffer;
	Mai_Quene0* write_buffer;
public:
	Mai_TCP_Client(Mai_I8* host, Mai_I8* port);
	~Mai_TCP_Client();
	Mai_Status Proc();
	Mai_Status Proc2();
	virtual Mai_Status ErrorR();
	Mai_Status closeC();
	Mai_Quene0* getReadQuene();
	Mai_Quene0* getWriteQuene();
	Mai_Status getStatus();
};*/







/* Mai_FTP_Server */



