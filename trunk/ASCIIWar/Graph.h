#pragma once
#include "common.h"


//���ڿ���ASCIIͼ�ε���
class Graph
{
private:
	Graph();
	~Graph();

public:
	static Graph* GetSingleton();
	void Destroy();							//�ݻٱ�����
	void InitWnd( int wid, int hei );		//��ʼ������
	void Flush();							//���󱸻�����ʾ������
	void ClearBuffer();						//�������
	void SetCaption( const char* name );	//���ô��ڱ���
	void DrawGrid( int x, int y, char dat, int bgColor, int fgColor );
											//��ĳһ�������

private:
	static Graph* m_me;						//���汾ͼ����ĵ���ָ��
	HANDLE m_cmd;							//�����д��ڵľ��

	SMALL_RECT m_wndRect;					//��������
	CHAR_INFO* m_buffer;					//ͼ�񻺳���
	COORD m_bufferSize;						//�����С

};

#define DRAW	(*Graph::GetSingleton())
