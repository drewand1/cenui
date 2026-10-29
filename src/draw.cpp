#include <cenui/draw.h>

void cenui::drawFrameRecursive(cenui::Frame* frame, sf::RenderWindow& window, sf::Vector2f parentPosition, sf::Vector2f parentSize) {
	sf::Vector2f absSz = sf::Vector2f(
		frame->size().scale.x * parentSize.x,
		frame->size().scale.y * parentSize.y
	) + frame->size().offset;
	sf::Vector2f absPos = sf::Vector2f(
		frame->position().scale.x * parentSize.x - absSz.x * frame->anchor().x,
		frame->position().scale.y * parentSize.y - absSz.y * frame->anchor().y
	) + frame->position().offset + parentPosition;
	sf::Vector2f contentPos = absPos + sf::Vector2f(frame->padding().left, frame->padding().top);
	sf::Vector2f contentSz = absSz - sf::Vector2f(
		frame->padding().left + frame->padding().right,
		frame->padding().top + frame->padding().bottom
	);
	
	static sf::RectangleShape rect;
	rect.setSize(absSz);
	rect.setPosition(absPos);
	rect.setFillColor(frame->bgColor());
	rect.setOutlineColor(frame->outlineColor());
	rect.setOutlineThickness(frame->outlineThickness());
	rect.setTexture(frame->texturePtr());

	window.draw(rect);

	if (frame->text()[0] != '\0') {
		sf::FloatRect textBounds = frame->textBounds();
		sf::Vector2f textPos(0, 0);

		switch (frame->textXAlignment()) {
		case cenui::XAlignment::LEFT:
			textPos.x = contentPos.x;
			break;

		case cenui::XAlignment::MIDDLE:
			textPos.x = contentPos.x + contentSz.x * 0.5f - textBounds.size.x * 0.5f;
			break;

		case cenui::XAlignment::RIGHT:
			textPos.x = contentPos.x + contentSz.x - textBounds.size.x - frame->padding().right;
			break;
		}

		switch (frame->textYAlignment()) {
		case cenui::YAlignment::TOP:
			textPos.y = contentPos.y + frame->padding().top;
			break;

		case cenui::YAlignment::MIDDLE:
			textPos.y = contentPos.y + contentSz.y * 0.5f - textBounds.size.y * 0.5f;
			break;

		case cenui::YAlignment::BOTTOM:
			textPos.y = contentPos.y + contentSz.y - textBounds.size.y - frame->padding().bottom;
			break;
		}

		frame->getSFText().setPosition(textPos);
		window.draw(frame->getSFText());
	}

	if (frame->getFirstChild()) {
		drawFrameRecursive(frame->editFirstChild(), window, contentPos, contentSz);
	}

	if (frame->getNextSibling()) {
		drawFrameRecursive(frame->editNextSibling(), window, parentPosition, parentSize);
	}
}