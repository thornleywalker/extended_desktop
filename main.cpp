#include <iostream>
#include <Windows.h>
#include <WinUser.h>

#define SCREEN_LEFT 0
#define SCREEN_RIGHT 1599
#define SCREEN_TOP 0
#define SCREEN_BOTTOM 899
#define TOP_BOTTOM_THRESHOLD 200

#define KEYSTROKE_TIME_LENGTH 100

using namespace std;


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
}

int main()
{
	//create cursor object
	POINT* cursorPos = new POINT();
	while (true)
	{
		//continuously poll for position
		GetCursorPos(cursorPos);

		//test output for position
		//cout << cursorPos->x << '\t' << cursorPos->y << endl;


		
		//right switch
		
		if (cursorPos->x == SCREEN_RIGHT &&
			cursorPos->y >= SCREEN_TOP + TOP_BOTTOM_THRESHOLD &&
			cursorPos->y <= SCREEN_BOTTOM - TOP_BOTTOM_THRESHOLD
			)
			
		//for(int i = 0; i < 1000; i++)
		{
			SetCursorPos(SCREEN_LEFT + 1, cursorPos->y);
			SwitchDesktopRight();
		}

		//left switch
		if (cursorPos->x == SCREEN_LEFT &&
			cursorPos->y >= SCREEN_TOP + TOP_BOTTOM_THRESHOLD &&
			cursorPos->y <= SCREEN_BOTTOM - TOP_BOTTOM_THRESHOLD
			)
		{
			SetCursorPos(SCREEN_RIGHT - 1, cursorPos->y);
			SwitchDesktopLeft();
		}
	}


	return 0;
}