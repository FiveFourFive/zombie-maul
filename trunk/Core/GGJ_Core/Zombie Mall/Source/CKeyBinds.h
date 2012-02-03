//#ifndef _CKEYBINDS_H
//#define _CKEYBINDS_H
//
//#include <Windows.h>
//#include <XInput.h>
//#include "CStopWatch.h"
//#pragma comment(lib,"xinput.lib")
//
//// fill this out with all of the actions that can be performed
//enum names{attack = 0, numactions};
//
//class CKeyBinds
//{
//private:
//	ButtonBind gamepadkeys[numactions];
//
//	int attack;
//
//
//public:
//
//	struct ButtonBind
//	{
//		int id; // set this to enum 
//		//char Event[32];
//		int button;
//	}
//
//	CKeyBinds();
//	~CKeyBinds();
//
//	RegisterButton(int button, char* Event);
//	bool Check(int id) // send in the id of the button you want to check
//	{
//		for(int i = 0; i < 4; i++)
//		{
//			if(gamepadkeys[i].id == id)
//			{
//				return gamepadkeys[i].gamepad.check(gamepadkeys[i].button);
//			}
//		}
//		return false;
//	}
//	// changebind(int id, int button)
//	// check if it is already bound
//	// using button
//	// if it is bound, unbind it
//	// set the new buttonbind[id] to button
//
//};
//
//
//
//#endif