#include "Mission1.h"
#include "Mission2.h"
#include "Mission3.h"
#include "Main Menu.h"

int main()
{

	RenderWindow MENU(VideoMode(1024, 600), "MAIN MENU");
	MainMenu mainMenu(MENU.getSize().x, MENU.getSize().y);

	while (MENU.isOpen()) {
		Event event;
		while (MENU.pollEvent(event)) {
			if (event.type == Event::Closed) {
				MENU.close();
			}
			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::Up) {
					mainMenu.MoveUp();
					break;
				}
				if (event.key.code == Keyboard::Down) {
					mainMenu.MoveDown();
					break;
				}
				if (event.key.code == Keyboard::Enter) {
					RenderWindow M1(VideoMode(1024, 600), "MISSION 1");
					RenderWindow M2(VideoMode(1024, 600), "MISSION 2");
					RenderWindow M3(VideoMode(1024, 600), "MISSION 3");
					RenderWindow INFO(VideoMode(1024, 600), "INFO");

					int x = mainMenu.MainMenuPressed();
					if (x == 0) {
						while (M1.isOpen()) {
							Event aevent;
							while (M1.pollEvent(aevent)) {
								if (aevent.type == Event::Closed) {
									M1.close();
								}
								if (aevent.type == Event::KeyPressed) {
									if (aevent.key.code == Keyboard::Escape) {
										M1.close();
									}
								}
							}
							M2.close();
							M3.close();
							INFO.close();
							M1.clear();
							Mission1* Go;
							Go = new Mission1(1024, 600);
							Go->Loop();
							M1.display();
						}
					}
					if (x == 1) {
						while (M2.isOpen()) {
							Event aevent;
							while (M2.pollEvent(aevent)) {
								if (aevent.type == Event::Closed) {
									M2.close();
								}
								if (aevent.type == Event::KeyPressed) {
									if (aevent.key.code == Keyboard::Escape) {
										M2.close();
									}
								}
							}
							M1.close();
							M2.clear();
							M3.close();
							INFO.close();
							Mission2* Go;
							Go = new Mission2(1024, 600);
							Go->Loop();
							M2.display();
						}
					}
					if (x == 2) {
						while (M3.isOpen()) {
							Event aevent;
							while (M3.pollEvent(aevent)) {
								if (aevent.type == Event::Closed) {
									M3.close();
								}
								if (aevent.type == Event::KeyPressed) {
									if (aevent.key.code == Keyboard::Escape) {
										M3.close();
									}
								}
							}
							M1.close();
							M3.clear();
							M2.close();
							INFO.close();
							Mission3* Go;
							Go = new Mission3(1024, 600);
							Go->Loop();
							M3.display();
						}
					}
					if (x == 3) {
						while (INFO.isOpen()) {
							Event aevent;
							while (INFO.pollEvent(aevent)) {
								if (aevent.type == Event::Closed) {
									INFO.close();
								}
								if (aevent.type == Event::KeyPressed) {
									if (aevent.key.code == Keyboard::Escape) {
										INFO.close();
									}
								}
							}
							M1.close();
							M2.close();
							M3.close();
							INFO.clear();
							INFO.display();
						}
					}
					if (x == 4) {
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