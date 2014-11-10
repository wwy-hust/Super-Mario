#ifndef MaiProcess_h
#define MaiProcess_h

/* MaiProcess */
class MaiProcess
{
private:
	Heap_Alloc0 heap0;

private:
	Mai_WChar* cmd;
	struct
	{
		Mai_WChar* args;
		Mai_I32 n;
		Mai_I32 n_max;
	} args;
	Mai_I32 argnum;

public:
	struct
	{
		HANDLE std_in_r;
		HANDLE std_in_w;
		HANDLE std_out_r;
		HANDLE std_out_w;
		Mai_Bool is_created;
	} mpipe;

private:
	//pid_t pid;
	PROCESS_INFORMATION pi;

public:
	MaiProcess();
	~MaiProcess();
	Mai_Status setCommand(Mai_WChar* cmd);
	Mai_Status pushArg(Mai_WChar* arg);
	Mai_Status makePipe();
	Mai_I32 readPipe(Mai_Void* b, Mai_I32 off, Mai_I32 len);
	Mai_I32 writePipe(Mai_Void* b, Mai_I32 off, Mai_I32 len);
	Mai_Status open();
	Mai_Status wait();
};

#endif

