/*****************************************************
CDesktop.h
*****************************************************/

#pragma once
#include <windows.h> 

class CDesktop {
public:
	CDesktop();
	~CDesktop();

	void SaveMode();
	void ResetMode();
	bool ChangeMode(int width, int height);

private:
	DEVMODE	devmode_saved;	// 保存的当前分辨率
	bool	mode_changed;	// 分辨率是否改变
} ;

