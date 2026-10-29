#include <iostream>
#include "cenui/frame.h"
#include "cenui/err.h"

namespace cenui {

Frame::Frame(std::string i)
	: id(i), mText(noFont, "", 30u) {mText.setFillColor({0, 0, 0, 255});}

Frame::Frame(std::string i, UIDimensions p, UIDimensions s)
	: id(i), mPosition(p), mSize(s), mText(noFont, "", 30u) {mText.setFillColor({0, 0, 0, 255});}

Frame::Frame(std::string i, const Frame* proto) 
	: id(i), mPosition(proto->mPosition), mSize(proto->mSize), mVisible(proto->mVisible),
	mAnchor(proto->mAnchor), mPadding(proto->mPadding), mBgColor(proto->mBgColor),
	mOutlineColor(proto->mOutlineColor), mOutlineThickness(proto->mOutlineThickness),
	mText(proto->mText), mTextXAlignment(proto->mTextXAlignment),
	mTextYAlignment(proto->mTextYAlignment), mTexturePtr(proto->mTexturePtr)
{
	if (!proto) {
		rtWarn("Attempt to copy a nullptr prototype on frame ID " + i);
		return;
	}
	
	const Frame* currentChild = proto->getFirstChild();
	while (currentChild) {
		Frame* newChild = new Frame(currentChild->id, currentChild);

		if (newChild) {
			newChild->appendTo(this);
		}

		currentChild = currentChild->nextSibling;
	}

	mText.setFillColor({0, 0, 0, 255});
}

Frame::~Frame() {
	Frame* currentChild = firstChild;
	Frame* nextChild = firstChild ? firstChild->nextSibling : nullptr;

	while (currentChild) {
		delete currentChild;
		currentChild = nextChild;
		nextChild = currentChild ? currentChild->nextSibling : nullptr;
	}
}

std::string Frame::ID() const {return id;}
UIDimensions Frame::position() const {return mPosition;}
UIDimensions Frame::size() const {return mSize;}
sf::Vector2f Frame::anchor() const {return mAnchor;}
Padding Frame::padding() const {return mPadding;}
sf::Color Frame::bgColor() const {return mBgColor;}
sf::Color Frame::outlineColor() const {return mOutlineColor;}
float Frame::outlineThickness() const {return mOutlineThickness;}
std::string Frame::text() const {return mText.getString().toAnsiString();}
const sf::Font& Frame::font() const {return mText.getFont();}
unsigned int Frame::characterSize() const {return mText.getCharacterSize();}
std::uint32_t Frame::textStyle() const {return mText.getStyle();}
sf::Color Frame::textColor() const {return mText.getFillColor();}
sf::Color Frame::textOutlineColor () const {return mText.getOutlineColor();}
float Frame::textOutlineThickness() const {return mText.getOutlineThickness();}
sf::FloatRect Frame::textBounds() const {return mText.getGlobalBounds();}
XAlignment Frame::textXAlignment() const {return mTextXAlignment;}
YAlignment Frame::textYAlignment() const {return mTextYAlignment;}
sf::Texture* Frame::texturePtr() const {return mTexturePtr;}
bool Frame::visible() const {return mVisible;}
const Frame* Frame::getFirstChild() const {return firstChild;}
const Frame* Frame::getNextSibling() const {return nextSibling;}
sf::Text& Frame::getSFText() {return mText;}
ClickCallback Frame::onClick() const {return mOnClick;}


const Frame* Frame::getChildByID(std::string id) const {
	Frame* child = firstChild;

	while (child) {
		if (child->id == id)
			return child;
	}

	return nullptr;
}

Frame* Frame::position(const UIDimensions& pos) {
	mPosition = pos;
	return this;
}

Frame* Frame::size(const UIDimensions& sz) {
	mSize = sz;
	return this;
}

Frame* Frame::anchor(const sf::Vector2f& an) {
	mAnchor = an;
	return this;
}

Frame* Frame::padding(const Padding& pd) {
	mPadding = pd;
	return this;
}

Frame* Frame::bgColor(const sf::Color& color) {
	mBgColor = color;
	return this;
}

Frame* Frame::outlineColor(const sf::Color& color) {
	mOutlineColor = color;
	return this;
}

Frame* Frame::outlineThickness(const float& thickness) {
	mOutlineThickness = thickness;
	return this;
}

Frame* Frame::text(const std::string& str) {
	mText.setString(str);
	return this;
}

Frame* Frame::text(const std::string& str, const sf::Font& fnt, unsigned int chSz) {
	mText.setFont(fnt);
	mText.setCharacterSize(chSz);
	mText.setString(str);
	return this;
}

Frame* Frame::font(const sf::Font& fnt){
	mText.setFont(fnt);
	return this;
}

Frame* Frame::characterSize(unsigned int chSz) {
	mText.setCharacterSize(chSz);
	return this;
}

Frame* Frame::textStyle(std::uint32_t style) {
	mText.setStyle(style);
	return this;
}

Frame* Frame::textColor(const sf::Color& color) {
	mText.setFillColor(color);
	return this;
}

Frame* Frame::textOutlineColor (const sf::Color& color) {
	mText.setOutlineColor(color);
	return this;
}

Frame* Frame::textOutlineThickness(float thickness) {
	mText.setOutlineThickness(thickness);
	return this;
}

Frame* Frame::textXAlignment(const XAlignment& alignment) {
	mTextXAlignment = alignment;
	return this;
}

Frame* Frame::textYAlignment(const YAlignment& alignment) {
	mTextYAlignment = alignment;
	return this;
}

Frame* Frame::texturePtr(sf::Texture* tex) {
	mTexturePtr = tex;
	return this;
}

Frame* Frame::visible(bool v) {
	mVisible = v;
	return this;
}

Frame* Frame::onClick(ClickCallback fn) {
	mOnClick = fn;
	return this;
}

// Makes the frame the child of the argument.
Frame* Frame::appendTo(Frame* other) {
	if (!other) {
		rtWarn("Attempt to append frame ID '" + id + "' to null frame.");
		return this;
	}

	if (parent) {
		emancipate();
	}

	if (!other->firstChild) {
		other->firstChild = this;
		parent = other;
	} else {
		Frame* child = other->firstChild;

		while (child->nextSibling) {
			if (child->id == id) {
				rtWarn("Attempt to append non-unique ID '"
				+ std::string(id)
				+ "' to frame ID '"
				+ std::string(other->id)
				+ "'."
			);
				return this;
			}

			child = child->nextSibling;
		}

		if (child->id == id) {
			rtWarn("Attempt to append non-unique ID '"
				+ std::string(id)
				+ "' to frame ID '"
				+ std::string(other->id)
				+ "'."
			);
			return this;
		}

		child->nextSibling = this;
		parent = other;
	}

	return this;
}

Frame* Frame::append(Frame* other) {
	other->appendTo(this);
	return other;
}

// Removes the frame from child-ship of the parent.
void Frame::emancipate() {
	// TODO: this lol
}

Frame* Frame::editFirstChild() {
	return firstChild;
}

Frame* Frame::editNextSibling() {
	return nextSibling;
}

Frame* Frame::editChildByID(const std::string& id) {
	Frame* child = firstChild;

	while (child) {
		if (child->id == id)
			return child;
	}

	return nullptr;
}

}