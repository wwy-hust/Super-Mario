/************************************************************************/
/*																		*/
/* 利用引擎编写坦克大战游戏             						        */
/* 作者：万立中	(C)2012-05-12											*/
/* www.wanlizhong.com													*/
/*																		*/
/************************************************************************/

#include "CMap.h"
#include <fstream>
#include <sstream>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMap::CMap()
{
	xOffset = 0;
	mapLevel = 0;
	isMapMoving = false;
}

CMap::~CMap()
{
	tileBmp->Destroy();
	delete tileBmp;
	releaseMapMatrix();
}

string& CMap::trim(string &s)
{
	if (s.empty()) {
		return s;
	}
	s.erase(0,s.find_first_not_of(" "));
	s.erase(s.find_last_not_of(" ") + 1);
	return s;
}

void CMap::GetTxtMapValue(string str, char* keywords, int& value)
{
	int pos;
	pos = str.find(keywords);
	if(pos !=-1)
	{
		pos=str.find("=");
		value = atoi(str.substr(pos+1, strlen(str.c_str())).c_str());
	}
}

void CMap::GetTxtMapValue(string str, char* keywords, string& value)
{
	int pos;
	pos = str.find(keywords);
	if(pos !=-1)
	{
		pos=str.find("=");
		value = str.substr(pos+1, strlen(str.c_str())).c_str();
	}
}

void CMap::initMapMatrix(int col, int row, int init_val)
{
#ifdef DEBUG
	char buf[64];
	sprintf(buf, "para:%d %d %d\n", col, row, init_val);
	OutputDebugString(buf);
#endif
	mapBackMatrix = new int*[row];//创建行指针数组
	mapBarrierMatrix = new int*[row];//创建行指针数组
	for(int r = 0; r<row; r++)
	{
		mapBackMatrix[r] = new int[col];//为每一行分配空间
		mapBarrierMatrix[r] = new int[col];//为每一行分配空间
		for(int c=0; c<col; c++)
		{
			mapBackMatrix[r][c] = init_val;
			mapBarrierMatrix[r][c] = init_val;
		}
	}
#ifdef DEBUG
	OutputDebugString("init matrix ok!\n");
#endif
}

void CMap::releaseMapMatrix()
{
	for(int r = 0; r<MapRows; r++)
	{
		delete [] mapBackMatrix[r];//删除每一行分配的空间
		delete [] mapBarrierMatrix[r];
	}
	delete [] mapBackMatrix;
	delete [] mapBarrierMatrix;
}

void CMap::setBackMatrix(int col, int row, int tileIndex)
{
	try{
		if ((col < 0) || (col >= MapCols) || (row < 0) || (row >= MapRows)) 
		{
			throw TEXT("矩阵索引值无效！");
		}
	}
	catch(char* sz){
		OutputDebugString(sz);
	}

	try{
		if (tileIndex > 0)
		{
			if (tileIndex >= (MapCols*MapRows))
				throw TEXT("图块索引值无效！");
		}
	}
	catch(char* sz){
		OutputDebugString(sz);
	}

	mapBackMatrix[row][col] = tileIndex;
	mapUpdated = true;
}

int CMap::getBackMatrix(int col, int row)
{
	if ((col < 0) || (col >= MapCols) || (row < 0) || (row >= MapRows)) 
	{
		throw L"矩阵索引值无效！";
	}

	return mapBackMatrix[row][col];
}

void CMap::setBarrierMatrix(int col, int row, int tileIndex)
{
	if ((col < 0) || (col >= MapCols) || (row < 0) || (row >= MapRows)) 
	{
		throw L"矩阵索引值无效！";
	}

	if (tileIndex > 0)
	{
		if (tileIndex >= (MapCols*MapRows))
			throw L"图块索引值无效！";
	}

	mapBarrierMatrix[row][col] = tileIndex;
	mapUpdated = true;
}

int CMap::getBarrierMatrix(int col, int row)
{
	if ((col < 0) || (col >= MapCols) || (row < 0) || (row >= MapRows)) 
	{
		throw L"矩阵索引值无效！";
	}
	return mapBarrierMatrix[row][col];
}

void CMap::LoadTxtMap(const char* txtmap_path)
{
	string str;
	ifstream infile(txtmap_path,ios::in);
	if(!infile){
#ifdef DEBUG
		OutputDebugString("\n**Open Map File Error!**\n");
#endif
		return;
	}
	char* lineStr = new char[2048];

	string mapback;
	string mapbarrier;

	bool startReadMapBack=false;
	bool startReadMapBarrier=false;

	while(!infile.eof())
	{
		infile.getline(lineStr, 2048);
		GetTxtMapValue(string(lineStr), "map_width", MapCols);
		GetTxtMapValue(string(lineStr), "map_height", MapRows);
		GetTxtMapValue(string(lineStr), "tile_width", TileWidth);
		GetTxtMapValue(string(lineStr), "tile_height", TileHeight);
		GetTxtMapValue(string(lineStr), "image_path", TileImagePath);

		if(string(lineStr).find("back")!=-1)
		{
			GetTxtMapValue(string(lineStr), "back", mapback);
			startReadMapBack = true;
			startReadMapBarrier = false;
		}
		if(startReadMapBack == true)
		{
			if(string(lineStr).find("=") == -1 && strlen(lineStr)>0)
			{
				mapback = mapback+string(lineStr);
			}
		}


		if(string(lineStr).find("barrier")!=-1)
		{
			GetTxtMapValue(string(lineStr), "barrier", mapbarrier);
			startReadMapBarrier = true;
			startReadMapBack = false;
		}
		if(startReadMapBarrier == true)
		{
			if(string(lineStr).find("=") == -1 && strlen(lineStr)>0)
			{
				mapbarrier = mapbarrier+string(lineStr);
			}
		}
	}

	delete[] lineStr;

	if(strlen(TileImagePath.c_str())>0)
	{
		LPTSTR pth = (char*)TileImagePath.c_str();
		tileBmp = new CGdiBmp(pth);
	}

	initMapMatrix(MapCols, MapRows, 0);
	mapUpdated = true;

	int pos =0;
	int t_col =0;
	int t_row = 0;
	while(pos !=-1 && t_row<MapRows)
	{
		pos= mapback.find(',');
		int gid = atoi(mapback.substr(0,pos).c_str());
		mapback = mapback.substr(pos+1, mapback.size());
		setBackMatrix(t_col, t_row, gid);

		pos= mapbarrier.find(',');
		gid = atoi(mapbarrier.substr(0,pos).c_str());
		mapbarrier = mapbarrier.substr(pos+1, mapbarrier.size());
		setBarrierMatrix(t_col, t_row, gid);

		t_col = t_col + 1;
		if(t_col==MapCols)
		{
			t_col = 0;
			t_row = t_row + 1;
		}
	}
#ifdef DEBUG
	printMap();
#endif
}

void CMap::DrawMap(HDC hDC, int x, int y)									
{
	HDC FrameDC = CreateCompatibleDC(GetDC(0));
	HBITMAP OldFrameBmp = (HBITMAP)SelectObject(FrameDC, tileBmp->GetBitmap());

	int tX = 0, tY = 0;
	int r = 0, c = 0;
	int img_col = 0, img_row = 0;
	int tileIndex = 0;

	for (r = 0, tY = y; r < MapRows; r++, tY += TileHeight)
	{
		for (c = 0, tX = x; c < MapCols; c++, tX += TileWidth)
		{
			int imgTotalCols = tileBmp->getBmpWidth()/TileWidth;
			tileIndex = mapBackMatrix[r][c];

			//tileIndex = tileIndex + 1;//Tile图片第一块为空

			//得到图片上的行列号
			img_col = (tileIndex-1)%imgTotalCols;
			img_row = (tileIndex-1-img_col)/imgTotalCols;

			StretchBlt(	hDC, tX, tY, TileWidth, TileHeight, 
				FrameDC, img_col*TileWidth, img_row*TileHeight, 
				TileWidth, TileHeight, SRCCOPY );
		}
	}

	SelectObject(FrameDC, OldFrameBmp);
	DeleteDC(FrameDC);
	DeleteObject(OldFrameBmp);
}

void CMap::DrawMap(HDC hDC)
{
	DrawMap(hDC, xOffset, 0);
}

void CMap::printMap()
{
	int r, c;
	int tW, tH;
	r = MapRows;
	c = MapCols;
	tW = TileWidth;
	tH = TileHeight;
	int i, j;
	char buf[32];
	sprintf(buf, "Rows:%d\n", r);
	OutputDebugString(buf);
	sprintf(buf, "Cols:%d\n", c);
	OutputDebugString(buf);
	sprintf(buf, "Tile:[%d,%d]\n", tW, tH);
	OutputDebugString(buf);

	for(i = 0; i < r; i++){
		for(j = 0; j < c; j++){
			sprintf(buf, "%d ", mapBackMatrix[i][j]);
			OutputDebugString(buf);
		}
		OutputDebugString("\n");
	}
	OutputDebugString("***********************************\n");
	for(i = 0; i < r; i++){
		for(j = 0; j < c; j++){
			sprintf(buf, "%d ", mapBarrierMatrix[i][j]);
			OutputDebugString(buf);
		}
		OutputDebugString("\n");
	}
}

void CMap::MoveMap()
{
	if(isMapMoving)
		xOffset -= MAP_MOVESPEED;
}
