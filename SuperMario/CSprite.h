/************************************************************************/
/*																		*/
/* 角色行为控制与交互实现		              						    */
/* 作者：万立中	(C)2009-09-07											*/
/* www.wanlizhong.com													*/
/*																		*/
/************************************************************************/

#include "CGdiBmp.h"
#include  <math.h>
#include "CMap.h"
#include "CEngine.h"
#include "debug_Global.h"

//防止编译时出现类重复定义的错误
#ifndef CSPRITE
#define CSPRITE
#define ROUND(x) (int)(x+0.5)//四舍五入的宏

/***********************************************************/
/*     
/* CSprite类定义
/*
/***********************************************************/
class CSprite  
{
private:
	//计算缩放后的帧图尺寸
	SIZE getRatioSize();
	//返回收缩后的碰撞矩形区域
	RECT GetShrinkRect(int shrinkRatio);
	//计算x、y轴的速率, xRatio和yRatio为输出参数
	void getXYRation(POINT lastPos, POINT newMousePos, 
		             double& xRatio, double& yRatio);
	//不允许调用默认构造函数
	CSprite();
	//重力下降速度 - add by wwy
	int downVelocity;
	//全局的位置

protected:
	//======================================================================
	//
	// 与帧图像相关的属性
	//
	//======================================================================
	CGdiBmp* spdib;				//原始精灵图片
	COLORREF transColor;		//精灵图片背景颜色(透明色)
	int totalFrames;			//精灵图片总帧数
	int rowFrames;				//精灵图片每行的帧数
	SIZE FrameSize;				//每帧精灵图片的宽、高
	int frameCount;				//精灵当前帧
	double ratio;				//放大或缩小比率(大于1放大，小于1缩小)		
	int mirror;					//是否镜像变换(0不变换，1左右镜像，2上下镜像)

	//======================================================================
	//
	// 与状态相关的属性
	//
	//======================================================================
	POINT globalPos;			//精灵在全局的地图中的坐标
	POINT pos;					//精灵当前坐标
	int dir;					//精灵当前方向
	int lastDir;				//上一次方向值
	bool active;				//精灵的状态（是否移动）
	bool visible;				//精灵在屏幕上是否可见
	int speed;					//移动的速度
	bool dead;					//精灵是否是死亡状态
	int restLife;				//精灵剩余的生命条数
	int	score;					//精灵的分值
	bool isJumping;				//精灵是否正在跳跃
	bool isFalling;				//精灵是否正在跌落
	int jumpTime;				//记录跳动的时间
	
public:
	CSprite(LPTSTR fileName);
	virtual ~CSprite();
	
	//======================================================================
	//
	// 表示方向的枚举值
	//
	//======================================================================
	enum
	{
		DIR_LEFT		= 0,	//左
		DIR_RIGHT		= 1,	//右
	};

	//======================================================================
	//
	// 与帧图像相关的获取与设置属性的方法
	//
	//======================================================================
	//获取位图对象
	virtual CGdiBmp* getDIB(){return spdib;}
	//设置透明色
	virtual void setTransRGB(COLORREF TransColor){transColor = TransColor;}
	//获取和设置原始图片总帧数
	virtual int getTotalFrames(){return totalFrames;}
	virtual void setTotalFrames(int totalFrameNum){totalFrames = totalFrameNum;} 
	//获取和设置原始图片中每行的帧图片数
	virtual int getRowFrames(){return rowFrames;}
	virtual void setRowFrames(int rowFrameNum){rowFrames = rowFrameNum;}
	//获取和设置帧图片的宽高
	virtual SIZE getFrameSize(){return FrameSize;}
	virtual void setFrameSize(SIZE frmSize){ FrameSize = frmSize;}
	//当前帧计数
	virtual int getFrameCount(){ return frameCount; }
	//获取和设置放大或缩小比率
	virtual double getRatio(){return ratio;}					
	virtual void setRatio(double r){ratio = r;}
	//获取和设置镜像模式(0不变换，1左右镜像，2上下镜像)
	virtual int getMirror(){return mirror;};	
	virtual void setMirror(int m){mirror = m;};	
	//获取和设置全局的位置
	virtual POINT getGlobalPos(){return globalPos;}
	virtual void setGlobalPos(POINT pos){globalPos = pos;}

	//======================================================================
	//
	// 与状态相关的获取与设置属性的方法
	//
	//======================================================================
	//获取和设置位置坐标
	virtual POINT getPos(){ POINT pt = {pos.x,pos.y}; return pt;}
	virtual void setPos(POINT pt){ pos = pt;}
	//获取和设置方向值
	virtual int getDirection(){return dir;}
	virtual void setDirection(int Dir){dir = Dir;}
	//获取和设置前一次的方向
	virtual int getLastDir(){return lastDir;}
	virtual void setLastDir(int dir){lastDir = dir;}
	//获取和设置可否移动属性
	virtual bool getActive(){return active;}
	virtual void setActive(bool spActive){active = spActive;}
	//获取和设置可见性
	virtual bool getVisible(){return visible;}
	virtual void setVisible(bool Visible){visible = Visible;}
	//获取和设置移动速度
	virtual int getSpeed(){ return speed;}
	virtual void setSpeed(int speedval){speed = speedval;}
	//获取和设置死亡状态
	virtual bool getDead(){return dead;}
	virtual void setDead(bool Dead){dead = Dead;}
	//获取和设置精灵的等级
	virtual int getRestLife(){return restLife;}
	virtual void setRestLife(int rL){restLife = rL;}
	//获取和设置精灵的分值
	virtual int getScore(){return score;}
	virtual void setScore(int sValue){score = sValue;}
	//获取和设置精灵的 Jumping
	virtual bool getJumping(){return isJumping;}
	virtual void setJumping(bool j){isJumping = j;}
	//获取和设置精灵的 Falling
	virtual bool getFalling(){return isFalling;}
	virtual void setFalling(bool f){isFalling = f;}
	//======================================================================
	//
	// 帧序列值的更新及精灵动画的绘制
	//
	//======================================================================
	//更新精灵动画帧计数
	virtual bool UpdateFrame(bool isLoop);
	//绘制精灵动画
	virtual void DrawAnimation(HDC hDC);

	//======================================================================
	//
	// 边界检测及碰撞检测
	//
	//======================================================================
	//检查精灵是否到达边界
	virtual bool CheckBound(RECT bound, int dir=-1);
	//检测本精灵对象是否与目标精灵碰撞, distance检测碰撞的距离
	virtual bool CollideWith(CSprite* target, int distance=0);
	//测试精灵是否到达该滚动背景的边界
	virtual bool CheckMoveBound();
	//测试该点是否是障碍
	virtual bool isPosBarrier(POINT aPos);
	//======================================================================
	//
	// 敌方精灵行为控制
	//
	//======================================================================
	//随机更新精灵方向
	virtual void UpdateDirection();	
	//自动更新精灵位置(keyPressed为真表示按下键盘)
	virtual void UpdatePosition(RECT bound, bool keyPressed=false);	
};

//======================================================================
//
//根据缩放系数计算帧图片宽、高
//
//=====================================================================
inline SIZE CSprite::getRatioSize()
{ 
	SIZE ratioFrameSize;
	ratioFrameSize.cx = ROUND(ratio*FrameSize.cx);
	ratioFrameSize.cy = ROUND(ratio*FrameSize.cy); 
	return ratioFrameSize;
}

//======================================================================
//
//返回当前碰撞矩形区域(收缩计算后的结果)
//
//======================================================================
inline RECT CSprite::GetShrinkRect(int shrinkRatio)
{
	RECT shrinkRect;
	SIZE ratioFrameSize = getRatioSize();

	shrinkRect.left = pos.x;
	shrinkRect.top = pos.y;
	shrinkRect.right = pos.x+ratioFrameSize.cx;
	shrinkRect.bottom = pos.y+ratioFrameSize.cy;

	int iXShrink = (shrinkRect.left-shrinkRect.right)/shrinkRatio;
	int iYShrink = (shrinkRect.top-shrinkRect.bottom)/shrinkRatio;
	InflateRect(&shrinkRect, iXShrink, iYShrink); //收缩矩形区域
	return shrinkRect;
}

//======================================================================
//
//检测本精灵对象是否与目标精灵碰撞(distance参数为检测距离)
//
//======================================================================
inline bool CSprite::CollideWith(CSprite* target, int distance)
{
	//计算参与碰撞检测的精灵矩形区域
	RECT rcThis = GetShrinkRect(5);
	RECT tmpRect = target->GetShrinkRect(5);
	RECT rcTest;
	rcTest.left =tmpRect.left-distance;
	rcTest.top = tmpRect.top-distance;
	rcTest.right = tmpRect.right+distance;
	rcTest.bottom = tmpRect.bottom+distance;
		        
	/********************************************
	//方式一：同时满足4个条件
	return rcThis.left <= rcTest.right &&
		   rcTest.left <= rcThis.right &&
		   rcThis.top <= rcTest.bottom &&
		   rcTest.top <= rcThis.bottom;
	*********************************************/

	int cw = rcThis.right - rcThis.left;
	int tw = rcTest.right - rcTest.left;
	int ch = rcThis.bottom - rcThis.top;
	int th = rcTest.bottom - rcTest.top;
	
	//方式二：同时满足2个条件
	return (abs((rcThis.left + cw/2)-(rcTest.left + tw/2))<(cw+tw)/2) &&
	       (abs((rcThis.top + ch/2)-(rcTest.top + th/2))<(ch+th)/2);
}

//------------------------------------------------------------------------
//
//根据两个参数指定的坐标计算x、y轴的速率（斜角移动的速度）
//xRatio与yRatio为输出参数, 即最终计算结果
//
//------------------------------------------------------------------------
inline void CSprite::getXYRation(POINT lastPos, POINT newMousePos, 
						         double& xRatio, double& yRatio)
{
	double aX,bY,Bias;
	
	//计算缩放后的帧图尺寸
	SIZE ratioFrameSize = getRatioSize();
	
	if(newMousePos.x > lastPos.x)
	{
		aX = newMousePos.x - (lastPos.x + ratioFrameSize.cx/2);
	}
	else
	{
		aX = (lastPos.x + ratioFrameSize.cx/2) - newMousePos.x;
	}
	
	if(newMousePos.y > lastPos.y)
	{
		bY = newMousePos.y - (lastPos.y + ratioFrameSize.cy/2);	
	}
	else
	{
		bY = (lastPos.y + ratioFrameSize.cy/2) - newMousePos.y;	
	}
	
	Bias = sqrt(aX*aX+bY*bY);
	xRatio = aX/Bias;
	yRatio = bY/Bias;
	
	if(lastPos.x-newMousePos.x == 0) xRatio = 0;
	if(lastPos.y-newMousePos.y == 0) yRatio = 0;
	if(lastPos.x-newMousePos.x > 0) xRatio = -xRatio;
	if(lastPos.y-newMousePos.y > 0) yRatio = -yRatio;
}

#endif