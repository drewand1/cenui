#ifndef CENUI_DRAW_H
#define CENUI_DRAW_H

#include <SFML/Graphics.hpp>
#include "cenui/frame.h"

namespace cenui {

void drawFrameRecursive(Frame* frame, sf::RenderWindow& window, sf::Vector2f parentPosition, sf::Vector2f parentSize);

}

#endif