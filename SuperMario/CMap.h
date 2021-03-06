/************************************************************************/
/*																		*/
/* 利用引擎编写坦克大战游戏             						        */
/* 作者：万立中	(C)2012-05-12											*/
/* www.wanlizhong.com													*/
/*																		*/
/************************************************************************/

#pragma once
#include "CGdiBmp.h"
#include <string>
#include <list>
#include "debug_Global.h"
using namespace std;

#define DEBUG

class CMap  
{
public:
	CMap();
	virtual ~CMap();

public:
	void LoadTxtMap(const char* txtmap_path);
	void DrawMap(HDC hDC, int x, int y);
	void DrawMap(HDC hDC);	//draw Moved Map
	void MoveMap();			//call ecery time when update

	string& trim(string &s);//删除字符串前后的空格
	void GetTxtMapValue(string str, char* keywords, int& value);
	void GetTxtMapValue(string str, char* keywords, string& value);

	void initMapMatrix(int col, int row, int init_val=0);
	void releaseMapMatrix();

	void setBackMatrix(int col, int row, int tileIndex);
	int getBackMatrix(int col, int row);

	void setBarrierMatrix(int col, int row, int tileIndex);
	int getBarrierMatrix(int col, int row);

	int getMapCols(){return MapCols;}
	int getMapRows(){return MapRows;}

	int getTileWidth(){return TileWidth;}
	int getTileHeight(){return TileHeight;}

	int getXOffset(){return xOffset;}
	void setXOffset(int x){xOffset = x;}

	bool getIsMapMoving(){return isMapMoving;}
	void setMapMoving(bool m){isMapMoving = m;}

	bool isPosZero(int row, int col){return mapBarrierMatrix[row][col] == 0 ? true : false;}
	void printMap();
	int getMapLevel(){return mapLevel;}
	void setMapLevel(int s){mapLevel = s;}

private:
	int** mapBackMatrix;
	int** mapBarrierMatrix;
	bool mapUpdated;
	int mapLevel;

	CGdiBmp* tileBmp;
	string TileImagePath;
	int TileWidth, TileHeight;	//单一图块的大小
	int TileNumInRow;			//图像文件中每行图块数
	int MapCols, MapRows;		//地图图块行列数
	int xOffset;				//地图的总的偏移量
	bool isMapMoving;			//地图是否应该移动
};