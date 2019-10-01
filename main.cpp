#include <iostream>
#include <Windows.h>
#include <WinUser.h>

#define SCREEN_LEFT 0
#define SCREEN_RIGHT 1599
#define SCREEN_TOP 0
#define SCREEN_BOTTOM 899
#define TOP_BOTTOM_THRESHOLD 200

using namespace std;


void SwitchDesktopRight()
{
	
}

void SwitchDesktopLeft()
{
	
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