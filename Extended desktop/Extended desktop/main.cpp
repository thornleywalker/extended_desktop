#include <iostream>
#include <Windows.h>
#include <WinUser.h>	// std::SendInput()
#include <thread>		// std::thread
#include <mutex>		// std::mutex
#include <condition_variable>//std::condition_variable::wait
#include <chrono>		// std::chrono::milliseconds

#define SCREEN_LEFT 0
#define SCREEN_RIGHT 1599
#define SCREEN_TOP 0
#define SCREEN_BOTTOM 899
#define TOP_BOTTOM_THRESHOLD 200

#define KEYSTROKE_TIME_LENGTH 100
#define DELAY_TIME_MS 100

#define DEBUG_ON 0

using namespace std;

void ReleaseKeys()
{
	//keystrokes
	KEYBDINPUT ctrlButton;
	ctrlButton.wVk = VK_CONTROL;
	ctrlButton.wScan = 0;
	ctrlButton.dwFlags = KEYEVENTF_KEYUP;
	ctrlButton.time = KEYSTROKE_TIME_LENGTH;
	ctrlButton.dwExtraInfo = 0;
	KEYBDINPUT windowsButton;
	windowsButton.wVk = VK_LWIN;
	windowsButton.wScan = 0;
	windowsButton.dwFlags = KEYEVENTF_KEYUP;
	windowsButton.time = KEYSTROKE_TIME_LENGTH;
	windowsButton.dwExtraInfo = 0;
	KEYBDINPUT leftButton;
	leftButton.wVk = VK_LEFT;
	leftButton.wScan = 0;
	leftButton.dwFlags = KEYEVENTF_KEYUP;
	leftButton.time = KEYSTROKE_TIME_LENGTH;
	leftButton.dwExtraInfo = 0;
	KEYBDINPUT rightButton;
	rightButton.wVk = VK_RIGHT;
	rightButton.wScan = 0;
	rightButton.dwFlags = KEYEVENTF_KEYUP;
	rightButton.time = KEYSTROKE_TIME_LENGTH;
	rightButton.dwExtraInfo = 0;

	//keyboard inputs
	INPUT ctrlInput;
	ctrlInput.type = INPUT_KEYBOARD;
	ctrlInput.ki = ctrlButton;
	INPUT windowsInput;
	windowsInput.type = INPUT_KEYBOARD;
	windowsInput.ki = windowsButton;
	INPUT leftInput;
	leftInput.type = INPUT_KEYBOARD;
	leftInput.ki = leftButton;
	INPUT rightInput;
	rightInput.type = INPUT_KEYBOARD;
	rightInput.ki = rightButton;

	INPUT keysUp[4] = { ctrlInput, windowsInput, leftInput, rightInput };

	SendInput(4, keysUp, 28);
}

void SwitchDesktopRight()
{

	//keystrokes
	KEYBDINPUT ctrlButton;
	ctrlButton.wVk = VK_CONTROL;
	ctrlButton.wScan = 0;
	ctrlButton.dwFlags = 0;
	ctrlButton.time = KEYSTROKE_TIME_LENGTH;
	ctrlButton.dwExtraInfo = 0;
	KEYBDINPUT windowsButton;
	windowsButton.wVk = VK_LWIN;
	windowsButton.wScan = 0;
	windowsButton.dwFlags = 0;
	windowsButton.time = KEYSTROKE_TIME_LENGTH;
	windowsButton.dwExtraInfo = 0;
	KEYBDINPUT rightButton;
	rightButton.wVk = VK_RIGHT;
	rightButton.wScan = 0;
	rightButton.dwFlags = 0;
	rightButton.time = KEYSTROKE_TIME_LENGTH;
	rightButton.dwExtraInfo = 0;

	//keyboard inputs
	INPUT ctrlInput;
	ctrlInput.type = INPUT_KEYBOARD;
	ctrlInput.ki = ctrlButton;
	INPUT windowsInput;
	windowsInput.type = INPUT_KEYBOARD;
	windowsInput.ki = windowsButton;
	INPUT rightInput;
	rightInput.type = INPUT_KEYBOARD;
	rightInput.ki = rightButton;


	//input array
	INPUT rightSwitch[3] = { ctrlInput, windowsInput, rightInput };
#if DEBUG_ON
	cout <<
#endif
		SendInput(3, rightSwitch, 28)
#if DEBUG_ON
		<< endl;
#else
		;
#endif
	ReleaseKeys();
}

void SwitchDesktopLeft()
{

	//keystrokes
	KEYBDINPUT ctrlButton;
	ctrlButton.wVk = VK_CONTROL;
	ctrlButton.wScan = 0;
	ctrlButton.dwFlags = 0;
	ctrlButton.time = KEYSTROKE_TIME_LENGTH;
	ctrlButton.dwExtraInfo = 0;
	KEYBDINPUT windowsButton;
	windowsButton.wVk = VK_LWIN;
	windowsButton.wScan = 0;
	windowsButton.dwFlags = 0;
	windowsButton.time = KEYSTROKE_TIME_LENGTH;
	windowsButton.dwExtraInfo = 0;
	KEYBDINPUT leftButton;
	leftButton.wVk = VK_LEFT;
	leftButton.wScan = 0;
	leftButton.dwFlags = 0;
	leftButton.time = KEYSTROKE_TIME_LENGTH;
	leftButton.dwExtraInfo = 0;

	//keyboard inputs
	INPUT ctrlInput;
	ctrlInput.type = INPUT_KEYBOARD;
	ctrlInput.ki = ctrlButton;
	INPUT windowsInput;
	windowsInput.type = INPUT_KEYBOARD;
	windowsInput.ki = windowsButton;
	INPUT leftInput;
	leftInput.type = INPUT_KEYBOARD;
	leftInput.ki = leftButton;

	//input array
	INPUT leftSwitch[3] = { ctrlInput, windowsInput, leftInput };

	#if DEBUG_ON
	cout <<
#endif
		SendInput(3, leftSwitch, 28)
#if DEBUG_ON
		<< endl;
#else
		;
#endif
	ReleaseKeys();
}

void MouseCheck(POINT* cursor)
{
	//poll for position
	GetCursorPos(cursor);

	//right switch
	if (cursor->x == SCREEN_RIGHT &&
		cursor->y >= SCREEN_TOP + TOP_BOTTOM_THRESHOLD &&
		cursor->y <= SCREEN_BOTTOM - TOP_BOTTOM_THRESHOLD
		)
	{
		SwitchDesktopRight();
		SetCursorPos(SCREEN_LEFT + 1, cursor->y);
	}

	//left switch
	if (cursor->x == SCREEN_LEFT &&
		cursor->y >= SCREEN_TOP + TOP_BOTTOM_THRESHOLD &&
		cursor->y <= SCREEN_BOTTOM - TOP_BOTTOM_THRESHOLD
		)
	{
		SwitchDesktopLeft();
		SetCursorPos(SCREEN_RIGHT - 1, cursor->y);
	}
}

int main()
{
	FreeConsole();
	//create cursor object
	POINT* cursorPos = new POINT();
	
	while (true)
	{
		if (MOUSEEVENTF_MOVE)
		{
			//if(DEBUG_ON) cout << "Mouse Move\n";
			MouseCheck(cursorPos);
		}
		else
		{
			//if(DEBUG_ON) cout << "No move\n";
		}
		Sleep(DELAY_TIME_MS);
	}
	return 0;
}