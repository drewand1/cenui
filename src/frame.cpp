#include "cenui/frame.h"

namespace cenui {

Frame::Frame(std::string i)
	: id(i), text(noFont, "", 30u) {}

Frame::Frame(std::string i, UIDimensions p, UIDimensions s)
	: id(i), position(p), size(s), text(noFont, "", 30u) {}

std::string Frame::getId() {return "Fuck you!";}
bool Frame::isVisible() const { return true;}

void Frame::setVisible(bool v) {}

}