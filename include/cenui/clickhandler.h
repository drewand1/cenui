#ifndef CENUI_CLICKHANDLER_H
#define CENUI_CLICKHANDLER_H

#include <cenui/frame.h>

namespace cenui {

class ClickHandler {
public:
	explicit ClickHandler(Frame* r);

	void handleMouseDown(const sf::RenderWindow& win);
	void handleMouseUp(const sf::RenderWindow& win);
	
private:
	Frame* root = nullptr;
	Frame* downFrame = nullptr;
};


}

#endif