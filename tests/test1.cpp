#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cenui.h>
#include <iostream>

sf::Font font("determination.ttf");

void clickCallback(cenui::Frame* clickedFrame) {
	std::cout << clickedFrame->ID() << std::endl;
}

cenui::Frame* makeButton(std::string id) {
	static float xCoord = 50;
	static bool giveOnClick = false;

	cenui::Frame* button = (new cenui::Frame(id))
		->position({{0, 0}, {xCoord, 350}})
		->size({{0, 0}, {100, 100}})
		->outlineColor({255, 0, 0, 255})
		->outlineThickness(3.0f)
		->text(id)
		->font(font)
		->characterSize(16u)
		->textColor({0, 0, 0, 255});
	
	if (giveOnClick)
		button->onClick(clickCallback);
	giveOnClick = !giveOnClick;
	xCoord += 50;
	return button;
}

cenui::Frame* makeChildButton(cenui::Frame* parent) {
	static bool giveOnClick = true;

	cenui::Frame* button = (new cenui::Frame(parent->ID() + "child"))
		->position({{0, 0}, {0, 50}})
		->size({{0, 0}, {100, 100}})
		->outlineColor({255, 0, 0, 255})
		->outlineThickness(3.0f)
		->text("ahahaha")
		->font(font)
		->characterSize(16u)
		->textColor({0, 0, 0, 255})
		->appendTo(parent);
	
	if (giveOnClick)
		button->onClick(clickCallback);
	giveOnClick = !giveOnClick;
	return button;
}

int main() {
	sf::RenderWindow window(sf::VideoMode({800, 600}), "test1");
	cenui::FrameManager frameMgr;

	for (int i = 0; i < 5; i++) {
		makeChildButton(makeButton(std::to_string(i))
			->appendTo(frameMgr.root()));
	}

	while (window.isOpen()) {
		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}

			if (const auto* resized = event->getIf<sf::Event::Resized>()) {
				sf::FloatRect newView({100.0f, 100.0f}, sf::Vector2f(resized->size));
				window.setView(sf::View(newView));
			}

			if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
				if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
					frameMgr.handleMouseDown(window);
				}
			}

			if (const auto* mouseButtonReleased = event->getIf<sf::Event::MouseButtonReleased>()) {
				if (mouseButtonReleased->button == sf::Mouse::Button::Left) {
					frameMgr.handleMouseUp(window);
				}
			}
		}

		window.clear(sf::Color::Black);
		frameMgr.drawFrames(window);
		window.display();
	}


	return 0;
}