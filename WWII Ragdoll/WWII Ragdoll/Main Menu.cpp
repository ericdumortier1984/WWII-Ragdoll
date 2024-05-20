#include "Main Menu.h"

MainMenu::MainMenu(float width, float height) 
{
	font.loadFromFile("Asset/junegull.ttf");

	title.setFont(font);
	title.setCharacterSize(50);
	title.setFillColor(Color::Red);
	title.setString("WWII RAGDOLL");
	title.setPosition(width/3, 50);
	//Mision 1 
	mainMenu[0].setFont(font);
	mainMenu[0].setCharacterSize(50);
	mainMenu[0].setFillColor(Color::White);
	mainMenu[0].setString("MISSION 1 (EASY)");
	mainMenu[0].setPosition(400, 130);
	//Mision 2
	mainMenu[1].setFont(font);
	mainMenu[1].setCharacterSize(50);
	mainMenu[1].setFillColor(Color::White);
	mainMenu[1].setString("MISSION 2 (NORMAL)");
	mainMenu[1].setPosition(400, 230);
	//Mision 3
	mainMenu[2].setFont(font);
	mainMenu[2].setCharacterSize(50);
	mainMenu[2].setFillColor(Color::White);
	mainMenu[2].setString("MISSION 3 (HARD)");
	mainMenu[2].setPosition(400, 330);
	//INFORMACION SOBRE EL JUEGO
	mainMenu[3].setFont(font);
	mainMenu[3].setCharacterSize(50);
	mainMenu[3].setFillColor(Color::White);
	mainMenu[3].setString("INFO");
	mainMenu[3].setPosition(400, 430);
	//SALIDA DEL JUEGO
	mainMenu[4].setFont(font);
	mainMenu[4].setCharacterSize(50);
	mainMenu[4].setFillColor(Color::White);
	mainMenu[4].setString("EXIT");
	mainMenu[4].setPosition(400, 530);

	MainMenuSelected = -1;
}

MainMenu::~MainMenu() 
{

}

void MainMenu::Draw(RenderWindow& window) 
{
	window.draw(title);
	for (int i = 0; i < Max_main_menu; i++) 
	{
		window.draw(mainMenu[i]);
	}
}

void MainMenu::MoveUp() 
{
	if (MainMenuSelected - 1 >= 0) 
	{
		mainMenu[MainMenuSelected].setFillColor(Color::White);
		MainMenuSelected--;
		if (MainMenuSelected == -1) 
		{
			MainMenuSelected == 2;
		}
		mainMenu[MainMenuSelected].setFillColor(Color::Yellow);
	}
}

void MainMenu::MoveDown() 
{
	if (MainMenuSelected + 1 <= Max_main_menu) 
	{
		mainMenu[MainMenuSelected].setFillColor(Color::White);
		MainMenuSelected++;
		if (MainMenuSelected == 5) 
		{
			MainMenuSelected == 0;
		}
		mainMenu[MainMenuSelected].setFillColor(Color::Yellow);
	}
}