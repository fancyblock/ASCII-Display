#pragma once
#include "common.h"


//用于控制ASCII图形的类
class Graph
{
private:
	Graph();
	~Graph();

public:
	static Graph* GetSingleton();
	void Destroy();							//摧毁本单件
	void InitWnd( int wid, int hei );		//初始化窗口
	void Flush();							//将后备缓冲显示到窗口
	void ClearBuffer();						//清除缓存
	void SetCaption( const char* name );	//设置窗口标题
	void DrawGrid( int x, int y, char dat, int bgColor, int fgColor );
											//画某一格的内容

private:
	static Graph* m_me;						//保存本图像类的单件指针
	HANDLE m_cmd;							//命令行窗口的句柄

	SMALL_RECT m_wndRect;					//窗口区域
	CHAR_INFO* m_buffer;					//图像缓冲区
	COORD m_bufferSize;						//缓冲大小

};

#define DRAW	(*Graph::GetSingleton())
