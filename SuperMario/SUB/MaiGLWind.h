#ifndef MaiGLWind_h
#define MaiGLWind_h

#include "SUB/Mai_All.h"
#include "SUB/Heap_Alloc0.h"

class MaiGLWind
{
public:
	virtual Mai_Status updateVelocity(float *v, float m, float time) = 0;
	virtual Mai_Status updateWind(float skip_time) = 0;
};

class MaiGLWindStatic : public MaiGLWind
{
private:
	float power[3];
public:
	MaiGLWindStatic(float *power);
	Mai_Status setPower(float *power);
	Mai_Status updateVelocity(float *v, float m, float time);
	Mai_Status updateWind(float skip_time);
};

class MaiGLWindRandom : public MaiGLWind
{
private:
	float power;
	float powers_now[3];
	float powers_last[3];
	float adtime[2];
	float time;
public:
	MaiGLWindRandom(float power, float alive_time, float dead_time);
	Mai_Status setPower(float power);
	Mai_Status setAliveTime(float alive_time);
	Mai_Status setDeadTime(float dead_time);
	Mai_Status makeWind();
	Mai_Status updateVelocity(float *v, float m, float time);
	Mai_Status updateWind(float skip_time);
};

#endif
