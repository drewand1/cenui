#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "cenui/frame.h"
#include "cenui/draw.h"
#include <iostream>

int main() {
	sf::Font font("determination.ttf");
	sf::RenderWindow window(sf::VideoMode({800, 600}), "test!");

	cenui::Frame* rootFrame = (new cenui::Frame("Hi!"))
		->bgColor({230, 230, 255, 255})
		->textXAlignment(cenui::XAlignment::LEFT)
		->textYAlignment(cenui::YAlignment::TOP)
		->text("Testing UI Library", font, 16u)
		->size({{0, 0}, {400, 300}})
		->position({{0.5f, 0.5f}, {0, 0}})
		->anchor({0.5f, 0.5f})
		->padding({5.0f, 5.0f, 5.0f, 5.0f});

	cenui::Frame* childFrame = (new cenui::Frame("childframe"))
		->position({{0.0f, 1.0f}, {0, 0}})
		->size({{0.4f, 0.5f}, {0, 0}})
		->anchor({0, 1.0f})
		->text("SUBFRAMES", font, 16u)
		->textColor({20, 20, 40, 255})
		->appendTo(rootFrame);

	cenui::Frame* copy = new cenui::Frame("copy", rootFrame);
	copy->position({{0, 0}, {0, 0}})->anchor({0, 0});
	cenui::Frame* test = (new cenui::Frame("childframe"))
		->appendTo(copy);

	std::cout << copy->getChildByID("childframe")->text() << std::endl;

	while (window.isOpen()) {
		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}

			if (const auto* resized = event->getIf<sf::Event::Resized>()) {
				sf::FloatRect newView({100.0f, 100.0f}, sf::Vector2f(resized->size));
				window.setView(sf::View(newView));
			}
		}

		window.clear();
		
		sf::View v = window.getView();
		sf::Vector2f topLeft(
			v.getCenter().x - v.getSize().x * 0.5,
			v.getCenter().y - v.getSize().y * 0.5
		);
		drawFrameRecursive(rootFrame, window, topLeft, v.getSize());
		drawFrameRecursive(copy, window, topLeft, v.getSize());

		window.display();
	}


	return 0;
}