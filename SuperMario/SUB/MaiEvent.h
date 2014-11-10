#ifndef MaiEvent_h
#define MaiEvent_h

#include "SUB/Mai_All.h"

class MaiEvent
{
private:
	volatile struct
	{
		HANDLE h_event;
	} infos;
public:
	MaiEvent(Mai_Bool initial_state = 0, Mai_Bool is_auto_event = 1);
	~MaiEvent();
	Mai_Status set();
	Mai_Status reset();
	Mai_Status wait();
};

#endif
