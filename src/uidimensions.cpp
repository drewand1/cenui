#include "cenui/uidimensions.h"

namespace cenui {

UIDimensions::UIDimensions(sf::Vector2f s, sf::Vector2f o)
	: scale(s), offset(o) {}

UIDimensions UIDimensions::operator+(const UIDimensions& other) {
	return UIDimensions(scale + other.scale, offset + other.offset);
}

UIDimensions UIDimensions::operator-(const UIDimensions& other) {
	return UIDimensions(scale - other.scale, offset - other.offset);
}

UIDimensions UIDimensions::operator-() {
	return UIDimensions({1.0f - scale.x, 1.0f - scale.y}, -offset);
}

UIDimensions UIDimensions::operator+=(const UIDimensions& other) {
	scale += other.scale;
	offset += other.offset;
	return *this;
}

UIDimensions UIDimensions::operator-=(const UIDimensions& other) {
	scale += other.scale;
	offset += other.offset;
	return *this;
}

UIDimensions UIDimensions::operator*=(float n) {
	scale *= n;
	offset *= n;
	return *this;
}

UIDimensions UIDimensions::operator/=(float n) {
	scale /= n;
	offset /= n;
	return *this;
}

UIDimensions operator*(float left, const UIDimensions& right) {
	return UIDimensions(right.scale * left, right.offset * left);
}

UIDimensions operator*(const UIDimensions& left, float right) {
	return right * left;
}

UIDimensions operator/(float left, const UIDimensions& right) {
	return UIDimensions(right.scale / left, right.offset / left);
}

UIDimensions operator/(const UIDimensions& left, float right) {
	return right / left;
}

}