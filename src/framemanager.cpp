#include "cenui/framemanager.h"
#include "cenui/err.h"
#include "cenui/draw.h"

namespace cenui {

FrameManager::FrameManager() : mRoot(new Frame("root")), clickHandler(mRoot) {
	assertWarn(mRoot, "FrameManager failed to allocate a root frame.");
	mRoot->bgColor({255, 255, 255, 0})->size({{1.0f, 1.0f}, {0.0f, 0.0f}});
}

FrameManager::~FrameManager() {
	if (mRoot) {
		delete mRoot;
	}
}

Frame* FrameManager::root() {
	return mRoot;
}

void FrameManager::drawFrames(sf::RenderWindow& window) {
	sf::View v = window.getView();
	sf::Vector2f topLeft(
		v.getCenter().x - v.getSize().x * 0.5,
		v.getCenter().y - v.getSize().y * 0.5
	);
	drawFrameRecursive(mRoot, window, topLeft, v.getSize());
}

void FrameManager::handleMouseDown(const sf::RenderWindow& window) {
	clickHandler.handleMouseDown(window);
}

void FrameManager::handleMouseUp(const sf::RenderWindow& window) {
	clickHandler.handleMouseUp(window);
}


}