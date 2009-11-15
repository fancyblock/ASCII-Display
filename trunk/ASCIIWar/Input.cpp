#include "Input.h"

Input::Input()
{
	m_input= GetStdHandle( STD_INPUT_HANDLE );
}

Input::~Input()
{
	CloseHandle( m_input );
}

bool Input::Update()
{
	DWORD info;

	DWORD evtNum;
	GetNumberOfConsoleInputEvents( m_input, &evtNum );

	if( evtNum == 0 )
	{
		m_key= false;
		m_mouse= false;
		return false;
	}

	if( ReadConsoleInput( m_input, &m_inputData, 1, &info ) )
	{
		if( info )
		{
			//有鼠标事件
			if( m_inputData.EventType == MOUSE_EVENT )
			{
				m_mouse= true;

				MOUSE_EVENT_RECORD& mse= m_inputData.Event.MouseEvent;
				DAT._x= mse.dwMousePosition.X;
				DAT._y= mse.dwMousePosition.Y;

				DAT._key= mse.dwButtonState;

				if( mse.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED )
				{
					m_mouseEvt= eLeftBt;
				
				}else if( mse.dwButtonState == RIGHTMOST_BUTTON_PRESSED )
				{
					m_mouseEvt= eRightBt;

				}else if( mse.dwEventFlags == DOUBLE_CLICK )
				{
					m_mouseEvt= eClick;
				
				}else
				{
					m_mouseEvt= eMoveMouse;
				}

				return true;

			}else
			{
				m_mouse= false;
			}

			//有键盘事件
			if( m_inputData.EventType == KEY_EVENT )
			{
				DAT._key= m_inputData.Event.KeyEvent.wVirtualKeyCode;
				m_key= m_inputData.Event.KeyEvent.bKeyDown;

				return true;
			}

		}
	}

	return false;
}
