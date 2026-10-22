#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "cenui/frame.h"
#include <iostream>

void drawFrame(cenui::Frame& frame, sf::RenderWindow& window, sf::Vector2f parentPosition, sf::Vector2f parentSize) {
	sf::Vector2f absSz = sf::Vector2f(
		frame.size.scale.x * parentSize.x,
		frame.size.scale.y * parentSize.y
	) + frame.size.offset;
	sf::Vector2f absPos = sf::Vector2f(
		frame.position.scale.x * parentSize.x - absSz.x * frame.anchor.x,
		frame.position.scale.y * parentSize.y - absSz.y * frame.anchor.y
	) + frame.position.offset + parentPosition;
	sf::Vector2f contentPos = absPos + sf::Vector2f(frame.padding.left, frame.padding.top);
	sf::Vector2f contentSz = absSz - sf::Vector2f(
		frame.padding.left + frame.padding.right,
		frame.padding.top + frame.padding.bottom
	);

	//sf::Vector2f contentPos = absPos;
	//sf::Vector2f contentSz = absSz;
	
	static sf::RectangleShape rect;
	rect.setSize(absSz);
	rect.setPosition(absPos);
	rect.setFillColor(frame.bgColor);
	rect.setOutlineColor(frame.outlineColor);
	rect.setOutlineThickness(frame.outlineThickness);
	rect.setTexture(frame.texturePtr);

	window.draw(rect);

	if (frame.text.getString()[0] != '\0') {
		sf::FloatRect textBounds = frame.text.getGlobalBounds();
		sf::Vector2f textPos(0, 0);

		switch (frame.textXAlignment) {
		case cenui::XAlignment::LEFT:
			textPos.x = contentPos.x;
			break;

		case cenui::XAlignment::MIDDLE:
			textPos.x = contentPos.x + contentSz.x * 0.5f - textBounds.size.x * 0.5f;
			break;

		case cenui::XAlignment::RIGHT:
			textPos.x = contentPos.x + contentSz.x - textBounds.size.x - frame.padding.right;
			break;
		}

		switch (frame.textYAlignment) {
		case cenui::YAlignment::TOP:
			textPos.y = contentPos.y + frame.padding.top;
			break;

		case cenui::YAlignment::MIDDLE:
			textPos.y = contentPos.y + contentSz.y * 0.5f - textBounds.size.y * 0.5f;
			break;

		case cenui::YAlignment::BOTTOM:
			textPos.y = contentPos.y + contentSz.y - textBounds.size.y - frame.padding.bottom;
			break;
		}

		frame.text.setPosition(textPos);
		window.draw(frame.text);
	}

	if (frame.firstChild) {
		drawFrame(*(frame.firstChild), window, contentPos, contentSz);
	}

	if (frame.nextSibling) {
		drawFrame(*(frame.nextSibling), window, parentPosition, parentSize);
	}
}

int main() {
	sf::Font font("determination.ttf");
	sf::RenderWindow window(sf::VideoMode({800, 600}), "test!");
	cenui::Frame f("Hi!");
	f.bgColor = {230, 230, 255, 255};
	f.textXAlignment = cenui::XAlignment::LEFT;
	f.textYAlignment = cenui::YAlignment::TOP;
	f.text = sf::Text(font, "Testing UI Library", 16u);
	f.text.setFillColor({20, 20, 40, 255});
	f.size = {{0, 0}, {400, 300}};
	f.position = {{0.5f, 0.5f}, {0, 0}};
	f.anchor = {0.5f, 0.5f};
	f.padding = {5.0f, 5.0f, 5.0f, 5.0f};

	cenui::Frame g("New", {{0.0f, 1.0f}, {0, 0}}, {{0.4f, 0.5f}, {0, 0}});
	g.anchor = {0, 1.0f};
	g.text = sf::Text(font, "SUBFRAMES", 16u);
	g.text.setFillColor({20, 20, 40, 255});
	f.firstChild = &g;

	while (window.isOpen()) {
		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
		}

		window.clear();

		drawFrame(f, window, {0, 0}, static_cast<sf::Vector2f>(window.getSize()));

		window.display();
	}


	return 0;
}