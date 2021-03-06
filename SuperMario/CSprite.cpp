/************************************************************************/
/*																		*/
/* 角色行为控制与交互实现		              						    */
/* 作者：万立中	(C)2009-09-07											*/
/* www.wanlizhong.com													*/
/*																		*/
/************************************************************************/

#include "CSprite.h"

extern CMap *map;

CSprite::CSprite(LPTSTR fileName)
{
	lastDir = DIR_LEFT;
	dir = DIR_LEFT;
	speed = 10;
	frameCount = 0;
	restLife = 0;
	visible = true;
	dead = false;
	spdib = new CGdiBmp(fileName);
	transColor = RGB(0,0,0);
	downVelocity = 0;
	isJumping = false;
	isFalling = false;
	jumpTime = 0;
}

CSprite::~CSprite()
{
}

//------------------------------------------------------------------------
//
//自动更新精灵方向
//
//------------------------------------------------------------------------
void  CSprite::UpdateDirection()
{
	lastDir=dir;  //上一次的方向
	do {
		dir = rand()% 2;
	}
	while(dir == lastDir);
}

//------------------------------------------------------------------------
//
// 根据限制范围更新精灵位置(keyPressed=true表示按下键盘)
//
//------------------------------------------------------------------------
void CSprite::UpdatePosition(RECT bound, bool keyPressed)
{/*
#ifdef DEBUG
	char b[64];
	sprintf(b, "Mario globalPos: [%d, %d]\n", getGlobalPos().x, getGlobalPos().y);
	OutputDebugString(b);
	sprintf(b, "Current Direction: %s\n", dir == DIR_LEFT ? "DIR_LEFT" : "DIR_RIGHT");
	OutputDebugString(b);
	sprintf(b, "Sprite Live : %s  | Sprite Active : %s\n", !dead ? "Live" : "Dead", active ? "True" : "False");
	OutputDebugString(b);
#endif
	if(active==true){
		if(!CheckBound(bound)){
			if(!keyPressed){
				//每隔一个不确定时间自动改变一次方向
				int r = rand()%100;
				if(r == 1){
					UpdateDirection();
				}
			}
#ifdef DEBUG
			char buf[64] = "Enter CSprite::UpdatePosition()\n";
			OutputDebugString(buf);
#endif
			POINT p;
			if(isJumping){		//跳跃的状态，此时为精灵向上运动
				p = getGlobalPos();
				jumpTime++;		//跳跃状态计时
				isFalling = true;		//一旦正在跳，即进入跌落的状态
				downVelocity -= JUMP_STRENGTH;
				if(abs(downVelocity) > map->getTileHeight())
					downVelocity = 0 - map->getTileHeight();
				p.y += downVelocity;
				if(isPosBarrier(p)){		//如果跳的时候上面是障碍物，则停止向上的运动，开始自由落体。
					globalPos.y -= globalPos.y % map->getTileHeight();
					downVelocity = 0;
					isJumping = false;
				}
				else{
					globalPos = p;
					isJumping = true;
				}
				if(jumpTime >= JUMP_TIME_LIMIT){
					isJumping = false;
				}
			}

			p = getGlobalPos();
			downVelocity += GRAVITY;		//计算重力的作用
			if(downVelocity >= map->getTileHeight())
				downVelocity = map->getTileHeight();
			p.y = p.y + downVelocity;
			POINT tmpPos = {p.x, p.y + FrameSize.cy};
			POINT tmpPos2 = {tmpPos.x, tmpPos.y -1};
			if(isPosBarrier(tmpPos)){		//落地
				globalPos.y = p.y - (p.y % map->getTileHeight());
				downVelocity = 0;
				isFalling = false;
				jumpTime = 0;		//落地了重新计时
			}
			else{	//向下没有障碍物，可以继续下坠
				globalPos = p;
				isFalling = true;
			}
#ifdef DEBUG
			sprintf(buf, "DownVelocity: %d\n", downVelocity);
			OutputDebugString(buf);
#endif
			p = getGlobalPos();
			switch(dir){
				case DIR_LEFT://左
					p.x = p.x - speed;
#ifdef DEBUG
					char buf[64];
					sprintf(buf, "IsPosZero In UpdatePosition(): %d\n", isPosBarrier(p));
					OutputDebugString(buf);
#endif
					if(!isPosBarrier(p))
						globalPos = p;
					else
						globalPos.x = globalPos.x;
					break;
				case DIR_RIGHT://右
					p.x = p.x + speed;
					tmpPos.x = p.x + (int)FrameSize.cx;
					tmpPos.y = p.y;
					if(!isPosBarrier(tmpPos))
						globalPos = p;
					else
						globalPos.x = p.x - (p.x % map->getTileWidth());
					break;
				default:
#ifdef DEBUG
					OutputDebugString("Update Sprite Position Into Default!\n");
#endif
					setDead(true);
					break;
			}
		}
		else{
			if(keyPressed == true && CheckBound(bound)){
				setActive(false);
			}
			else{
				//----------------------------------------------------------
				//到达边界改变方向
				//----------------------------------------------------------
				if(CheckBound(bound, DIR_LEFT)) setDirection(DIR_RIGHT);
				if(CheckBound(bound, DIR_RIGHT)) setDirection(DIR_LEFT);
				//到达左右边界后
				if(CheckBound(bound, DIR_LEFT)||CheckBound(bound, DIR_RIGHT)){
					int Top = bound.top;
					int Btm = bound.bottom;
					//移出屏幕后，随机改变y坐标值
					pos.y = (rand()%(Btm-Top))+Top;
					if(CheckBound(bound, DIR_LEFT)) setDirection(DIR_RIGHT);
					if(CheckBound(bound, DIR_RIGHT)) setDirection(DIR_LEFT);
				}
			}

		}
		pos.x = globalPos.x - map->getXOffset();
		pos.y = globalPos.y;
	}
	if(pos.x >= (200)){
		map->setMapMoving(true);
	}
	else{
		map->setMapMoving(false);
	}*/
}

//------------------------------------------------------------------------
//
// 测试该点是否是障碍   是返回 true
//
//------------------------------------------------------------------------
bool CSprite::isPosBarrier(POINT aPos)
{
	/*int tW, tH, maxX, maxY;
	int **barrier;

	tH = map->getTileHeight();
	tW = map->getTileWidth();
	maxX = aPos.x / tW;
	maxY = aPos.y / tH;

#ifdef DEBUG
	char buf[64];
	sprintf(buf, "IsPosZero: [%d, %d]\n", aPos.x, aPos.y);
	OutputDebugString(buf);
	sprintf(buf, "Map Tile:[%d, %d]\n", map->getTileHeight(), map->getTileWidth());
	OutputDebugString(buf);
#endif

	if(0 != map->getBarrierMatrix(maxX, maxY))
		return true;
	else
		return false;*/
	return 0;
}

//------------------------------------------------------------------------
//
// 根据限制范围检查精灵是否到达边界   是返回 true
//
//------------------------------------------------------------------------
bool CSprite::CheckBound(RECT bound, int Dir)
{
	bool atEdge = false;
	int d;

	if(Dir != -1)
		d = Dir;
	else
		d = dir;

	//计算缩放后的帧图尺寸
	SIZE ratioFrameSize = getRatioSize();

	//根据方向检查是否到达目的地
	switch(d)
	{
	case DIR_LEFT://左
		if(pos.x <= bound.left){
			atEdge = true;
		}
		break;
	case DIR_RIGHT://右
		if((pos.x-ratioFrameSize.cx) >= bound.right){
			atEdge = true;
		}
		break;
	default:
		atEdge = false;
	}
	return atEdge;
}

//------------------------------------------------------------------------
//
// 测试精灵是否到达该滚动背景的边界   是返回 true
//
//------------------------------------------------------------------------
bool CSprite::CheckMoveBound()
{
	return true;
}

//------------------------------------------------------------------------
//
// 动画帧计数
// 参数为真表示要循环播放动画，参数为表示假只播放一次
// 只播放一次返回值为假，循环播放返回值为真
//
//------------------------------------------------------------------------
bool CSprite::UpdateFrame(bool isLoop)
{
	bool KeepUpdating = true;
	frameCount = frameCount + 1;
	if(frameCount > totalFrames-1) 
	{
		if(isLoop) 
		{
			frameCount = 0;
			KeepUpdating = true;
		}
		if(!isLoop) 
		{
			frameCount = totalFrames-1;
			KeepUpdating = false;
		}	
	}
	return KeepUpdating;
}

void CSprite::DrawAnimation(HDC hDC)
{
	if(spdib != NULL)
	{
		if(this->getVisible())
		{
			switch(this->getDirection()){
				case CSprite::DIR_LEFT:
					this->setMirror(0);
					break;
				case CSprite::DIR_RIGHT:
					this->setMirror(1);
					break;
				default:
					this->setMirror(0);
					break;
			}
			spdib->DrawAnimatedFrames(
				hDC, pos.x, pos.y, frameCount, rowFrames, 
				FrameSize.cx, FrameSize.cy, ratio, mirror, 
				transColor);
		}
	}
}
