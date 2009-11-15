#pragma once
#include "common.h"

//鼠标事件
enum MOUSE_EVT
{
	eMoveMouse,
	eLeftBt,
	eRightBt,
	eClick,
};

//获取鼠标和键盘输入
class Input
{
public:
	Input();
	~Input();
	bool Update();
	bool IsKey(){	return m_key; }						//是键盘事件
	bool IsMouse(){	return m_mouse; }					//是鼠标事件
	int KeyEvtType(){ return m_keyEvt; }				//键盘事件类型
	int MouseEvtType(){ return m_mouseEvt; }			//鼠标事件类型

	struct
	{
		int _x;
		int _y;
		int _key;
	}DAT;												//存储鼠标坐标和键盘值信息

private:
	HANDLE m_input;
	INPUT_RECORD m_inputData;
	bool m_mouse;
	bool m_key;
	int m_keyEvt;
	MOUSE_EVT m_mouseEvt;

};
