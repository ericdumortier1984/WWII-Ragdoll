#include "Mission1.h"
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
					RenderWindow M1(VideoMode(1024, 600), "");
					RenderWindow OPTIONS(VideoMode(1024, 600), "OPTIONS");
					RenderWindow ABOUT(VideoMode(1024, 600), "ABOUT");

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
							OPTIONS.close();
							ABOUT.close();
							M1.clear();
							Mission1* Go;
							Go = new Mission1(1024, 600);
							Go->Loop();
							M1.display();
						}
					}
					if (x == 1) {
						while (OPTIONS.isOpen()) {
							Event aevent;
							while (OPTIONS.pollEvent(aevent)) {
								if (aevent.type == Event::Closed) {
									OPTIONS.close();
								}
								if (aevent.type == Event::KeyPressed) {
									if (aevent.key.code == Keyboard::Escape) {
										OPTIONS.close();
									}
								}
							}
							M1.close();
							OPTIONS.clear();
							ABOUT.close();
							OPTIONS.display();
						}
					}
					if (x == 2) {
						while (ABOUT.isOpen()) {
							Event aevent;
							while (ABOUT.pollEvent(aevent)) {
								if (aevent.type == Event::Closed) {
									ABOUT.close();
								}
								if (aevent.type == Event::KeyPressed) {
									if (aevent.key.code == Keyboard::Escape) {
										ABOUT.close();
									}
								}
							}
							M1.close();
							OPTIONS.close();
							ABOUT.clear();
							ABOUT.display();
						}
					}
					if (x == 3) {
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