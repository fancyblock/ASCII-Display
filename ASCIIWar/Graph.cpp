#include "Graph.h"

Graph* Graph::m_me= NULL;

Graph::Graph()
{
	m_cmd= NULL;
	m_buffer= NULL;
}

Graph::~Graph()
{
	CloseHandle( m_cmd );
}

//�õ�����
Graph* Graph::GetSingleton()
{
	if( m_me == NULL )
	{
		m_me= new Graph();
	}

	return m_me;

}

//�ݻٱ�����
void Graph::Destroy()
{
	if( m_me )
	{
		delete m_me;
		m_me= NULL;
	}

	if( m_buffer )
	{
		delete[] m_buffer;
		m_buffer= NULL;
	}

}

//��ʼ������
void Graph::InitWnd( int wid, int hei )
{
	//��ȡ������������
	m_cmd= GetStdHandle( STD_OUTPUT_HANDLE );

	//���ô��ڴ�С
	m_wndRect.Left= 0;
	m_wndRect.Top= 0;
	m_wndRect.Bottom= hei - 1;
	m_wndRect.Right= wid - 1;
	SetConsoleWindowInfo( m_cmd, true, &m_wndRect );

	//���ô��ڴ�С
	COORD cood;
	cood.X= wid;
	cood.Y= hei;
	SetConsoleScreenBufferSize( m_cmd, cood );

	//���ع��
	CONSOLE_CURSOR_INFO cursor;
	cursor.dwSize= 1;
	cursor.bVisible= false;
	SetConsoleCursorInfo( m_cmd, &cursor );

	//��������
	m_bufferSize.X= wid;		//�����С����
	m_bufferSize.Y= hei;
	m_buffer= new CHAR_INFO[wid * hei];
	//�����ʼ����
	memset( m_buffer, 0, sizeof(CHAR_INFO)*(wid*hei) );

}

//���󱸻�����ʾ������
void Graph::Flush()
{
	static COORD cod;
	cod.X= 0;
	cod.Y= 0;

	WriteConsoleOutput( m_cmd, m_buffer, m_bufferSize, cod, &m_wndRect );

}

//�������
void Graph::ClearBuffer()
{
	memset( m_buffer, 0, sizeof(CHAR_INFO)*(m_bufferSize.X * m_bufferSize.Y) );
}

//���ô��ڱ���
void Graph::SetCaption( const char* name )
{
	SetConsoleTitle( name );
}

//��ĳһ�������
void Graph::DrawGrid( int x, int y, char dat, int bgColor, int fgColor )
{
	if( x < 0 || y < 0 || x >= m_bufferSize.X || y >= m_bufferSize.Y )
	{
		return;
	}
	
	int pos= y * m_bufferSize.X + x;

	m_buffer[pos].Char.AsciiChar= dat;
	m_buffer[pos].Attributes= bgColor<<4 | fgColor;

}
											