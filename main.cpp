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

#define DELAY_TIME_MS 10

using namespace std;

timed_mutex mtx;

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
	cout << SendInput(3, rightSwitch, 28) << endl;
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

	cout << SendInput(3, leftSwitch, 28) << endl;
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
	this_thread::sleep_for(chrono::milliseconds(DELAY_TIME_MS));
}

int main()
{
	//create cursor object
	POINT* cursorPos = new POINT();
	HWND theWindow;
	WNDPROC windowProc;
	windowProc(theWindow, WM_MOUSEMOVE, 0, 0);
	
	while (true)
	{
		if (MOUSEEVENTF_MOVE)
		{
			cout << "Mouse Move\n";
			MouseCheck(cursorPos);
		}
		else
		{
			cout << "No move\n";
		}
		
	}


	return 0;
}