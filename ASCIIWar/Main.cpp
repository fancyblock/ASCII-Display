#include "common.h"

#include "Input.h"
#include "Graph.h"
#include <cstdlib>
#include <ctime>
#include <conio.h>

using namespace std;

//��ASCII����ĵ�һ��DEMO

//���ڵĿ��
const int SRC_WID= 80;
const int SRC_HEI= 30;
//��ľ��
const int ACOUNT= 400;
//����
const char SING= 'A';
//��ɫ���̣�
int BGCOLOR= 0;


//
int allGrid[SRC_WID][SRC_HEI];

//A�࣬���ڱ�ʾһ��A
class A
{
public:
	A(){}
	~A(){}
	bool update()
	{
		if( !m_active && m_y < (SRC_HEI - 1) && allGrid[m_x][m_y+1] == -1 )
		{
			int old= allGrid[m_x][m_y];
			allGrid[m_x][m_y]= -1;
			m_y++;
			allGrid[m_x][m_y]= old;
			return true;
		}
		return false;
	}

	bool m_active;
	int m_x;
	int m_y;
	int m_color;

};
//�洢���е�A
A allA[ACOUNT];

//����Ǹ�A������
int activex;	
int activey;

//����Ǹ�A������
int activeA;

//ѡȡ״̬
enum{ eNoSelect, eSelect };
int state= eNoSelect;

void reset();

int main()
{
	cout<<"[Pick A Demo]"<<endl;
	cout<<"use mouse to pick up 'A'"<<endl;
	cout<<"and you can put it in anywhere"<<endl;
	cout<<"write by Hjb"<<endl;
	cout<<""<<endl;
	getch();

	DRAW.SetCaption( "Pick A Demo" );
	DRAW.InitWnd( SRC_WID, SRC_HEI );

	//����
	Input ipt;

	reset();

	int i;

	DWORD time= GetTickCount();
	bool drawFlag;

	while( true )
	{
		drawFlag= false;

		DWORD refTime= GetTickCount();
		if( refTime - time > 100 )
		{
			for( i= 0; i< ACOUNT; i++ )
			{
				int tmpx= allA[i].m_x;
				int tmpy= allA[i].m_y;
				if( allA[i].update() )
				{
					DRAW.DrawGrid( tmpx, tmpy, 0, 0, 0 );
					DRAW.DrawGrid( allA[i].m_x, allA[i].m_y, SING, BGCOLOR, allA[i].m_color );
					drawFlag= true;
				}
			}
			time= refTime;
		}

		//����϶�ĳ��A
		ipt.Update();
		if( ipt.IsMouse() )
		{
			int evtType= ipt.MouseEvtType();

			activex= ipt.DAT._x;
			activey= ipt.DAT._y;

			switch( state )
			{
			case eNoSelect:
				if( evtType == eLeftBt )
				{
					activeA= allGrid[activex][activey];
					//ѡ����
					if( activeA != -1 )
					{
						allA[activeA].m_active= true;
						state= eSelect;
					}
				}
				break;
			case eSelect:
				if( evtType == eLeftBt )
				{
					//�϶���
					if( allGrid[activex][activey] == -1 )
					{
						DRAW.DrawGrid( allA[activeA].m_x, allA[activeA].m_y, 0, 0, 0 );
						allGrid[allA[activeA].m_x][allA[activeA].m_y]= -1;
						allGrid[activex][activey]= activeA;
						allA[activeA].m_x= activex;
						allA[activeA].m_y= activey;
						DRAW.DrawGrid( allA[activeA].m_x, allA[activeA].m_y, SING, BGCOLOR, allA[activeA].m_color );
						drawFlag= true;
					}
				}else if( evtType == eMoveMouse )
				{
					allA[activeA].m_active= false;
					state= eNoSelect;
				}
				break;
			default:
				break;
			}
		}else if( ipt.IsKey() )
		{
			if( ipt.DAT._key == VK_SPACE )
			{
				reset();
			}

		}

		if( drawFlag )
		{
			DRAW.Flush();
		}

	}

	DRAW.Destroy();

	return 0;
}

//����
void reset()
{
	//��ʼ��
	int i,j;
	for( i= 0; i< SRC_WID; i++ )
	{
		for( j= 0; j< SRC_HEI; j++ )
		{
			allGrid[i][j]= -1;
		}
	}

	//�������һ��A
	int colors[]= { 10,15,14,12 };
	srand( (unsigned int)time(0) );
	for( i= 0; i< ACOUNT; i++ )
	{
		int tx,ty;
		do
		{
			tx= rand()%SRC_WID;
			ty= rand()%SRC_HEI;
		}while( allGrid[tx][ty] != -1 );

		allA[i].m_active= false;
		allA[i].m_x= tx;
		allA[i].m_y= ty;
		allA[i].m_color= colors[i%4];

		allGrid[tx][ty]= i;
	}

	//��һ���ʼ����
	DRAW.ClearBuffer();
	for( i= 0; i< ACOUNT; i++ )
	{
		DRAW.DrawGrid( allA[i].m_x, allA[i].m_y, SING, BGCOLOR, allA[i].m_color );
	}
	DRAW.Flush();

	state= eNoSelect;

}
