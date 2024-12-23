#pragma once
#include "MainHeader.h"

#define Max_main_menu 5

class MainMenu 
{
private:
	int MainMenuSelected;
	Font font;
	Text mainMenu[Max_main_menu], title;
public:
	MainMenu(float width, float height);

	void Draw(RenderWindow& window);
	void MoveUp();
	void MoveDown();

	int MainMenuPressed() 
	{
		return MainMenuSelected;
	}
	~MainMenu();

};