#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cenui.h>
#include <iostream>



void clickCallback(cenui::Frame* clickedFrame) {
	std::cout << "Hello world!" << std::endl;
}

int main() {
	sf::Font font("determination.ttf");
	sf::RenderWindow window(sf::VideoMode({800, 600}), "test1");
	cenui::FrameManager frameMgr;

	cenui::Frame* panel = frameMgr.root()->append(new cenui::Frame("panel"))
		->anchor({0.5f, 0.5f})
		->position({{0.5f, 0.5f}, {0, 0}})
		->size({{0, 0}, {400, 300}});

	cenui::Frame* button = panel->append(new cenui::Frame("button"))
		->anchor({0.5f, 0.5f})
		->position({{0.5f, 0.5f}, {0, 0}})	// TODO: make overloads for u and f
		->size({{0, 0}, {200, 100}})
		->text("Click me!")
		->font(font)
		->characterSize(16u)
		->bgColor({200, 255, 200, 255})
		->onClick(clickCallback);


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
