# UIDimensions
```c++
sf::Vector2f scale = {0, 0};
sf::Vector2f offset = {0, 0};

UIDimensions(sf::Vector2f scale, sf::Vector2f offset);
UIDimensions operator+(const UIDimensions& other);
UIDimensions operator-(const UIDimensions& other);
UIDimensions operator-();
UIDimensions operator+=(const UIDimensions& other);
UIDimensions operator-=(const UIDimensions& other);
UIDimensions operator*=(float n);
UIDimensions operator/=(float n);

friend UIDimensions operator*(float left, const UIDimensions& right);
friend UIDimensions operator*(const UIDimensions& left, float right);
friend UIDimensions operator/(float left, const UIDimensions& right);
friend UIDimensions operator/(const UIDimensions& left, float right);
```