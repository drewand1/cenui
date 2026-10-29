#include <SFML/Graphics.hpp>
#include "cenui/clickhandler.h"
#include "cenui/err.h"

// Helper functions

cenui::Frame* findHoveredChildRecursive(cenui::Frame* frame, sf::Vector2f mousePos, sf::Vector2f parentPos, sf::Vector2f parentSz) {
	if (!frame->visible())
		return nullptr;

	sf::Vector2f absSz = sf::Vector2f(	// This is indeed duplicate code from drawFrameRecursive. I do not care!
		frame->size().scale.x * parentSz.x,
		frame->size().scale.y * parentSz.y
	) + frame->size().offset;
	sf::Vector2f absPos = sf::Vector2f(
		frame->position().scale.x * parentSz.x - absSz.x * frame->anchor().x,
		frame->position().scale.y * parentSz.y - absSz.y * frame->anchor().y
	) + frame->position().offset + parentPos;

	bool mouseInBounds = mousePos.x >= absPos.x && mousePos.y >= absPos.y && mousePos.x <= absPos.x + absSz.x && mousePos.y <= absPos.y + absSz.y;

		
	// need to do a post-order traversal among siblings because latter siblings are drawn
	// above former.
	if (frame->getNextSibling()) {
		cenui::Frame* siblingResult = findHoveredChildRecursive(frame->editNextSibling(), mousePos, parentPos, parentSz);
		if (siblingResult)
			return siblingResult;
	}

	if (!mouseInBounds)
		return nullptr;
	
	// If this frame has a click callback, disregard children and treat this
	// frame as the whole button.
	if (frame->onClick()) {
		return frame;
	}

	// Finally, if no overlapping siblings have a click function, and
	// nether does this frame, search through children.
	if (frame->getFirstChild()) {
		cenui::Frame* childResult = findHoveredChildRecursive(frame->editFirstChild(), mousePos, absPos, absSz);
		return childResult;
	}

	return nullptr;
}


// Class member functions

namespace cenui {

ClickHandler::ClickHandler(Frame* r) : root(r) {
	assertWarn(r, "Attempt to initialize click handler with nullptr root.");
}

void ClickHandler::handleMouseDown(const sf::RenderWindow& win) {
	if (!root)
		return;

	sf::View v = win.getView();
	sf::Vector2f topLeft(
		v.getCenter().x - v.getSize().x * 0.5f,
		v.getCenter().y - v.getSize().y * 0.5f
	);
	sf::Vector2f mPos = win.mapPixelToCoords(sf::Mouse::getPosition(win));
	std::cout << mPos.x << " "<< mPos.y << "\n";
	downFrame = findHoveredChildRecursive(root, win.mapPixelToCoords(sf::Mouse::getPosition(win)), topLeft, v.getSize());	
}
void ClickHandler::handleMouseUp(const sf::RenderWindow& win) {
	if (!root)
		return;

	sf::View v = win.getView();
	sf::Vector2f topLeft(
		v.getCenter().x - v.getSize().x * 0.5f,
		v.getCenter().y - v.getSize().y * 0.5f
	);

	cenui::Frame* hovered = findHoveredChildRecursive(root, win.mapPixelToCoords(sf::Mouse::getPosition(win)), topLeft, v.getSize());
	
	if (hovered && hovered == downFrame && hovered->onClick()) {
		hovered->onClick()(hovered);
	}
}

}