#include "common.h"

#include "Input.h"
#include "Graph.h"
#include <cstdlib>
#include <ctime>
#include <conio.h>

using namespace std;

//本ASCII引擎的第一个DEMO

//窗口的宽高
const int SRC_WID= 80;
const int SRC_HEI= 30;
//积木数
const int ACOUNT= 400;
//符号
const char SING= 'A';
//颜色（绿）
int BGCOLOR= 0;


//
int allGrid[SRC_WID][SRC_HEI];

//A类，用于表示一个A
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
//存储所有的A
A allA[ACOUNT];

//活动的那个A的坐标
int activex;	
int activey;

//活动的那个A的索引
int activeA;

//选取状态
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

	//输入
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

		//鼠标拖动某个A
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
					//选中了
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
					//拖动中
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

//重置
void reset()
{
	//初始化
	int i,j;
	for( i= 0; i< SRC_WID; i++ )
	{
		for( j= 0; j< SRC_HEI; j++ )
		{
			allGrid[i][j]= -1;
		}
	}

	//随机产生一批A
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

	//第一遍初始绘制
	DRAW.ClearBuffer();
	for( i= 0; i< ACOUNT; i++ )
	{
		DRAW.DrawGrid( allA[i].m_x, allA[i].m_y, SING, BGCOLOR, allA[i].m_color );
	}
	DRAW.Flush();

	state= eNoSelect;

}
