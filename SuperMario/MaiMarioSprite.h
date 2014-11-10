

#ifndef MaiMarioSprite_h
#define MaiMarioSprite_h

//#include "SuperMario.h"
#include "CSprite.h"
#include "Mai.h"
#include "debug_Global.h"

typedef struct _MaiMarioSpriteFrameInfo
{
	Mai_I32 frames[0x40];
	Mai_I32 n;
	Mai_I32 num;
} MaiMarioSpriteFrameInfo;

#define MaiMarioActionTypeStop 0
#define MaiMarioActionTypeRun 1
#define MaiMarioActionTypeJump 2
#define MaiMarioActionTypeDamaged 3

class MaiMarioSprite : public CSprite
{
private:
	struct
	{
		MaiMarioSpriteFrameInfo fi[0x10];
		Mai_I32 action_type[0x10];
		Mai_I32 n;
		Mai_I32 num;
	} frameinfo;
	struct
	{
		Mai_I32 action_now;
		Mai_Bool is_jump_key_already;
		Mai_Bool is_something_below;
	} infos;
	struct
	{
		float x, y;
		float speed_x, speed_y;
		float accel_x, accel_y;
	} spriteinfo;

	bool isGoingToDeath;
public:
	MaiMarioSprite(LPTSTR fileName);
	Mai_Status addAction(Mai_I32 *frames, Mai_I32 count, Mai_I32 type);
	Mai_Status setActionNow(Mai_I32 action_now);
	virtual void DrawAnimation(HDC hDC);
	virtual bool UpdateFrame(bool isLoop);
	void UpdatePosition(RECT bound, bool keyPressed);
	Mai_Bool is_sprite_ng();
	Mai_Status OnKeyDown(Mai_I32 wParam);
	bool GetIsGoingToDeath(){return isGoingToDeath;}
	void SetIsGoingToDeath(bool s){isGoingToDeath = s;}

	static MaiMarioSprite *getMainSprite();

	float getPosX(){return spriteinfo.x;};
	void initMarioSir();
	void CheckIfDeath();
};

#endif
