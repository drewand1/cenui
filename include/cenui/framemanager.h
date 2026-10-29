#ifndef CENUI_FRAMEMANAGER_H
#define CENUI_FRAMEMANAGER_H

#include <SFML/Graphics.hpp>
#include "cenui/frame.h"
#include "cenui/clickhandler.h"

namespace cenui {

class FrameManager {
public:
	FrameManager();
	~FrameManager();

	Frame* root();

	void drawFrames(sf::RenderWindow& window);
	void handleMouseDown(const sf::RenderWindow& window);
	void handleMouseUp(const sf::RenderWindow& window);

private:
	Frame* mRoot = nullptr;
	ClickHandler clickHandler;
};

}

#endif