#ifndef CENUI_FRAME_H
#define CENUI_FRAME_H

#include <list>
#include <string>
#include "cenui/uidimensions.h"

namespace cenui {

struct Padding {
	float left = 0.0f, right = 0.0f, top = 0.0f, bottom = 0.0f;
};

enum class YAlignment {
	TOP = 0,
	MIDDLE,
	BOTTOM
};

enum class XAlignment {
	LEFT = 0,
	MIDDLE,
	RIGHT
};
	
class Frame {
public:
	UIDimensions position = {{0, 0}, {0, 0}};
	UIDimensions size = {{0, 0}, {100.0f, 100.0f}};
	sf::Vector2f anchor = {0, 0};
	Padding padding;

	sf::Color bgColor = {255, 255, 255, 255};
	sf::Color outlineColor = {0, 0, 0, 255};
	float outlineThickness = 1.0f;

	sf::Text text;
	XAlignment textXAlignment = XAlignment::MIDDLE;
	YAlignment textYAlignment = YAlignment::MIDDLE;

	sf::Texture* texturePtr = nullptr;

	Frame* parent = nullptr;
	Frame* firstChild = nullptr;
	Frame* nextSibling = nullptr;

	void (*onClick)(const std::string& id) = nullptr;

	explicit Frame(std::string id);
	Frame(std::string id, UIDimensions pos, UIDimensions size);

	std::string getId();
	bool isVisible() const;

	void setVisible(bool v);

private:
	enum FrameFlagsIntl {
		REMAKE_RECT = 1 << 0,
		REMAKE_TEXT = 1 << 1,
		VISIBLE = 1 << 2
	};

	std::string id;
	FrameFlagsIntl flags = static_cast<FrameFlagsIntl>(REMAKE_RECT | REMAKE_TEXT | VISIBLE);

	inline static sf::Font noFont;
};

}

#endif