#include "MaiMarioSprite.h"
#include "CDxSound.h"

MaiMarioSprite *main_sprite_fj3rfr3289jf = 0;

extern CMap*			map;
extern CSprite*			coin;
extern CDxSoundBuffer	BGSound;
extern CDxSoundBuffer	JumpSound;
extern CDxSoundBuffer	DeadSound;
extern CDxSoundBuffer	GameTotallyEndSound;
extern CDxSoundBuffer	GameOverSound;
extern CDxSoundBuffer	EnterCastleSound;
extern CDxSoundBuffer	EnterTubeSound;
extern CDxSoundBuffer	DragFlagPloeSound;
extern CDxSoundBuffer	StepOnEnemySound;
extern CDxSoundBuffer	KnockBrickSound;
extern bool				inWelcome;
extern bool				inLevelBegin;
extern bool				inPlaying;
extern int				LifeRemain;
extern int				currentLevel;
extern long				oldTimeCount;
extern bool				UpGgradeLevel;
extern bool				isDragingFlag;
extern int				dragDistance;
extern bool				isGettingCoin;
extern int				coinCount;


MaiMarioSprite::MaiMarioSprite(LPTSTR fileName) : CSprite(fileName)
{
	Mai_memset(&frameinfo, 0, sizeof(frameinfo));
	Mai_memset(&infos, 0, sizeof(infos));
	frameinfo.num = 0x10;
	//初始化坐标速度加速度 其中xy分别为马里奥中心点坐标
	spriteinfo.x = 40.0f;
	spriteinfo.y = 40.0f;
	spriteinfo.accel_x = 0.0f;
	spriteinfo.accel_y = 2.0f;
	spriteinfo.speed_x = 0.0f;
	spriteinfo.speed_y = 0.0f;
	//frameinfo.fi[0].num = 
	//添加各动作对应的帧
	Mai_I32 stopframe[] = {0};
	addAction(stopframe, 1, MaiMarioActionTypeStop);
	Mai_I32 runframe[] = {1, 2, 3, 4, 5};
	addAction(runframe, 5, MaiMarioActionTypeRun);
	Mai_I32 jumpframe[] = {6};
	addAction(jumpframe, 1, MaiMarioActionTypeJump);
	Mai_I32 damagedframe[] = {7};
	addAction(damagedframe, 1, MaiMarioActionTypeDamaged);

	main_sprite_fj3rfr3289jf = this;
	isGoingToDeath = false;
}

//添加动作所对应的帧
Mai_Status MaiMarioSprite::addAction(Mai_I32 *frames, Mai_I32 count, Mai_I32 type)
{
	frameinfo.action_type[frameinfo.n] = type;
	for (Mai_I32 a0 = 0; a0 < count; a0++) frameinfo.fi[frameinfo.n].frames[a0] = frames[a0];
	frameinfo.fi[frameinfo.n].n = 0;
	frameinfo.fi[frameinfo.n++].num = count;
	return 0;
}


void MaiMarioSprite::DrawAnimation(HDC hDC)
{
	frameCount = frameinfo.fi[infos.action_now].frames[frameinfo.fi[infos.action_now].n];
	CSprite::DrawAnimation(hDC);
}

bool MaiMarioSprite::UpdateFrame(bool isLoop)
{//	printf("%d ", infos.action_now);
	frameinfo.fi[infos.action_now].n = (frameinfo.fi[infos.action_now].n + 1) % frameinfo.fi[infos.action_now].num;
	return CSprite::UpdateFrame(isLoop);
}

//设定当前的动作 将会影响动画的绘制
Mai_Status MaiMarioSprite::setActionNow(Mai_I32 action_now)
{
	if (infos.action_now != action_now)
	{
		infos.action_now = action_now;
		frameinfo.fi[infos.action_now].n = 0;
	}
	return 0;
}

MaiMarioSprite *MaiMarioSprite::getMainSprite()
{
	return main_sprite_fj3rfr3289jf;
}

Mai_Bool MaiMarioSprite::is_sprite_ng() //判断马里奥当前是否与其它物体重合
{
	Mai_I32 l0 = (Mai_I32)(spriteinfo.x - FrameSize.cx / 2);
	Mai_I32 t0 = (Mai_I32)(spriteinfo.y - FrameSize.cy / 2);
	Mai_I32 r0 = (Mai_I32)(spriteinfo.x + FrameSize.cx / 2);
	Mai_I32 b0 = (Mai_I32)(spriteinfo.y + FrameSize.cy / 2);

	if (l0 < 0) return 1;
	if (t0 < 0) return 1;
	if (r0 >= map->getMapCols() * map->getTileWidth()) return 1;
	if (b0 >= map->getMapRows() * map->getTileHeight()) return 1;

	Mai_I32 x_start = (Mai_I32)(spriteinfo.x / map->getTileWidth()) - 3;
	if (x_start < 0) x_start = 0;
	Mai_I32 x_end = x_start + 6;
	if (x_end > map->getMapCols()) x_end = map->getMapCols();
	Mai_I32 y_start = (Mai_I32)(spriteinfo.y / map->getTileHeight()) - 3;
	if (y_start < 0) y_start = 0;
	Mai_I32 y_end = y_start + 6;
	if (y_end > map->getMapRows()) y_end = map->getMapRows();

	for (Mai_I32 a0 = x_start; a0 < x_end; a0++)
	{
		for (Mai_I32 a1 = y_start; a1 < y_end; a1++)
		{
			Mai_I32 l1 = a0 * map->getTileWidth();
			Mai_I32 t1 = a1 * map->getTileHeight();
			Mai_I32 r1 = l1 + map->getTileWidth();
			Mai_I32 b1 = t1 + map->getTileHeight();
			if ( !( (l0 <= l1 && r0 <= l1) || (t0 <= t1 && b0 <= t1) || (l0 >= r1 && r0 >= r1) || (t0 >= b1 && b0 >= b1) ) )
			{
				if(map->getBarrierMatrix(a0, a1) && isDragingFlag)
					isDragingFlag = false;

				if(99 == map->getBarrierMatrix(a0, a1))
					UpGgradeLevel = true;

				//printf("%.4f %.4f %.4f\n", spriteinfo.accel_y, spriteinfo.speed_y, spriteinfo.y);
				if((2 == map->getBarrierMatrix(a0, a1) && spriteinfo.speed_y < -6) || 45 == map->getBarrierMatrix(a0, a1) || (a1 - 1 > 0 ? (45 == map->getBarrierMatrix(a0, a1 - 1) && spriteinfo.speed_y < -6) : false)){
					isGettingCoin = true;
					if(2 == map->getBarrierMatrix(a0, a1)){
						map->setBackMatrix(a0, a1, 1);
						map->setBarrierMatrix(a0, a1, 1);
					}
					else if(45 == map->getBarrierMatrix(a0, a1)){
						map->setBackMatrix(a0, a1, 32);
						map->setBarrierMatrix(a0, a1, 0);
					}
					else{
						map->setBackMatrix(a0, a1 - 1, 32);
						map->setBarrierMatrix(a0, a1 - 1, 0);
					}
					coinCount++;
					POINT pos;
					pos.x = (a0 * 16) + map->getXOffset();
					pos.y = a1 * 16;
					coin->setPos(pos);
					coin->setVisible(true);
				}

				if(11 == map->getBarrierMatrix(a0, a1) || 10 == map->getBarrierMatrix(a0, a1)){
					spriteinfo.speed_x = 0;
					spriteinfo.speed_y = 10;
					spriteinfo.accel_x = 0;
					map->setBarrierMatrix(a0, a1, 0);
					isDragingFlag = true;
					if(dragDistance == 0){
						dragDistance = spriteinfo.y;
					}
				}
				if (map->getBarrierMatrix(a0, a1)) return 1;
			}
		}
	}

	return 0;
}

Mai_Status MaiMarioSprite::OnKeyDown(Mai_I32 wParam)
{//printf("ccfds\n");
	/*if (infos.action_now != MaiMarioActionTypeJump)
	{
		if (wParam == (Mai_I32)'X')
		{
			spriteinfo.speed_y = -15.0f;
			setActionNow(MaiMarioActionTypeJump);
		}
	}*/
	return 0;
}

void MaiMarioSprite::UpdatePosition(RECT bound, bool keyPressed)
{
	if (GetAsyncKeyState(VK_LEFT) < 0 && !isDragingFlag)
	{
		spriteinfo.speed_x = -8.0f;
		setLastDir(CSprite::DIR_LEFT);
		setDirection(CSprite::DIR_LEFT);
	}
	else if (GetAsyncKeyState(VK_RIGHT) < 0 && !isDragingFlag)
	{
		spriteinfo.speed_x = 8.0f;
		setLastDir(CSprite::DIR_RIGHT);
		setDirection(CSprite::DIR_RIGHT);
	}
	else
	{
		spriteinfo.speed_x = 0.0f;
	}

	if (infos.action_now != MaiMarioActionTypeJump)
	{
		if (GetAsyncKeyState(VK_LEFT) < 0 && !isDragingFlag)
		{
			setActionNow(MaiMarioActionTypeRun);
		}
		else if (GetAsyncKeyState(VK_RIGHT) < 0 && !isDragingFlag)
		{
			setActionNow(MaiMarioActionTypeRun);
		}
		else
		{
			setActionNow(MaiMarioActionTypeStop);
		}

		if (GetAsyncKeyState((Mai_I32)'X') < 0)
		{
			if ( (infos.is_jump_key_already) && (infos.is_something_below) )
			{
				spriteinfo.speed_y = -15.0f;
				setActionNow(MaiMarioActionTypeJump);
				JumpSound.Play();
				infos.is_jump_key_already = 0;
			}
		}
		else
		{
			infos.is_jump_key_already = 1;
		}
	}

	float x_tmp = spriteinfo.x;
	spriteinfo.x += spriteinfo.speed_x; //尝试改变当前x坐标
	
	while (is_sprite_ng()) //如果当前与其它物体重合 则恢复原坐标 并降低速度继续尝试
	{
		spriteinfo.speed_x *= 0.9f;
		spriteinfo.x = x_tmp;
		spriteinfo.x += spriteinfo.speed_x;
		
		//spriteinfo.speed_x = 0;
	}
	spriteinfo.speed_x += spriteinfo.accel_x; //速度更新（加上加速度

	float y_tmp = spriteinfo.y;
	spriteinfo.y += spriteinfo.speed_y;
	
	infos.is_something_below = 0;

	if ( (spriteinfo.speed_y > 0.0f) && (is_sprite_ng()) ) //如果速度向下 并且尝试改变坐标时与其他物体重合
	{
		infos.is_something_below = 1;
		if (infos.action_now == MaiMarioActionTypeJump) setActionNow(MaiMarioActionTypeStop);
	}

	while (is_sprite_ng()) //如果当前与其它物体重合 则恢复原坐标 并降低速度继续尝试
	{
		spriteinfo.speed_y *= 0.9f;
		spriteinfo.y = y_tmp;
		spriteinfo.y += spriteinfo.speed_y;
	}
	spriteinfo.speed_y += spriteinfo.accel_y;

	//spriteinfo.speed_
	pos.x = (Mai_I32)(spriteinfo.x - FrameSize.cx / 2);
	pos.y = (Mai_I32)(spriteinfo.y - FrameSize.cy / 2);
	pos.x += map->getXOffset();

//	printf("%f %f\n", spriteinfo.x, spriteinfo.y);
	Mai_I32 xoff = (Mai_I32)spriteinfo.x - 200;
	if (xoff < 0) xoff = 0;
	if (xoff + 400 >= map->getMapCols() * map->getTileWidth()) xoff = map->getMapCols() * map->getTileWidth() - 400;
	map->setXOffset(xoff * (-1));
}

void MaiMarioSprite::initMarioSir()
{
	//初始化坐标速度加速度 其中xy分别为马里奥中心点坐标
	spriteinfo.x = 40.0f;
	spriteinfo.y = 40.0f;
	spriteinfo.accel_x = 0.0f;
	spriteinfo.accel_y = 2.0f;
	spriteinfo.speed_x = 0.0f;
	spriteinfo.speed_y = 0.0f;

	main_sprite_fj3rfr3289jf = this;
	isGoingToDeath = false;
}

void MaiMarioSprite::CheckIfDeath()
{
	//wwy add
	if(spriteinfo.y >= 200){
		isGoingToDeath = true;
		setActionNow(MaiMarioActionTypeStop);
		oldTimeCount = 0;
	}
}