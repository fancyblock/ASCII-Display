#pragma once
#include "common.h"

//����¼�
enum MOUSE_EVT
{
	eMoveMouse,
	eLeftBt,
	eRightBt,
	eClick,
};

//��ȡ���ͼ�������
class Input
{
public:
	Input();
	~Input();
	bool Update();
	bool IsKey(){	return m_key; }						//�Ǽ����¼�
	bool IsMouse(){	return m_mouse; }					//������¼�
	int KeyEvtType(){ return m_keyEvt; }				//�����¼�����
	int MouseEvtType(){ return m_mouseEvt; }			//����¼�����

	struct
	{
		int _x;
		int _y;
		int _key;
	}DAT;												//�洢�������ͼ���ֵ��Ϣ

private:
	HANDLE m_input;
	INPUT_RECORD m_inputData;
	bool m_mouse;
	bool m_key;
	int m_keyEvt;
	MOUSE_EVT m_mouseEvt;

};
