#include "Mission1.h"
#include "Mission2.h"
#include "Mission3.h"
#include "Main Menu.h"

int main()
{

	RenderWindow MENU(VideoMode(1024, 600), "MAIN MENU");
	MainMenu mainMenu(MENU.getSize().x, MENU.getSize().y);

	while (MENU.isOpen()) 
	{
		Event event;
		while (MENU.pollEvent(event)) 
		{
			if (event.type == Event::Closed) 
			{
				MENU.close();
			}
			if (event.type == Event::KeyPressed) 
			{
				if (event.key.code == Keyboard::Up)
				{
					mainMenu.MoveUp();
					break;
				}
				if (event.key.code == Keyboard::Down) 
				{
					mainMenu.MoveDown();
					break;
				}
				if (event.key.code == Keyboard::Enter) 
				{
					int x = mainMenu.MainMenuPressed();
					if (x == 0)
					{
						MENU.clear();
						Mission1* Go;
						Go = new Mission1(MENU.getSize().x, MENU.getSize().y);
						Go->Loop();
						MENU.display();
					}
					if (x == 1) 
					{
						MENU.clear();
						Mission2* Go;
						Go = new Mission2(MENU.getSize().x, MENU.getSize().y);
						Go->Loop();
						MENU.display();
					}
					if (x == 2) 
					{
						MENU.clear();
						Mission3* Go;
						Go = new Mission3(MENU.getSize().x, MENU.getSize().y);
						Go->Loop();
						MENU.display();
					}
					if (x == 3) 
					{
						MENU.clear();
						// Aqui va a ir la class INFO
						MENU.display();
					}
					if (x == 4) 
					{
						MENU.close();
						break;
					}
				}
			}
			MENU.clear();
			mainMenu.Draw(MENU);
			MENU.display();
		}
	}

	return EXIT_SUCCESS;
}