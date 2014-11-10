#ifndef MaiGLEmitter_h
#define MaiGLEmitter_h

#include "SUB/Mai_All.h"
#include "SUB/Heap_Alloc0.h"
#include "SUB/MaiCriticalSection.h"

class MaiGLEmitter
{
public:
	virtual Mai_Status makeParticle(float *co, float *v0) = 0;
};

class MaiGLEmitterPointShowLine : public MaiGLEmitter
{
private:
	float o[3];
	float v0[3];
public:
	MaiGLEmitterPointShowLine(float *o, float *v0);
	Mai_Status makeParticle(float *co, float *v0);
};

class MaiGLEmitterPointShowBall : public MaiGLEmitter
{
private:
	float o[3];
	float v0;
public:
	MaiGLEmitterPointShowBall(float *o, float v0);
	Mai_Status makeParticle(float *co, float *v0);
	Mai_Status setPos(float *o);
};

#endif

