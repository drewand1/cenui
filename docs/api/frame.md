# Frame
```c++
explicit Frame(std::string id);
Frame(std::string i, const Frame* prototype);
Frame(std::string id, UIDimensions pos, UIDimensions size);
~Frame();

// Getters
std::string ID() const;
UIDimensions position() const;
UIDimensions size() const;
sf::Vector2f anchor() const;
Padding padding() const;
sf::Color bgColor() const;
sf::Color outlineColor() const;
float outlineThickness() const;
std::string text() const;
const sf::Font& font() const;
unsigned int characterSize() const;
std::uint32_t textStyle() const;
sf::Color textColor() const;
sf::Color textOutlineColor () const;
float textOutlineThickness() const;
sf::FloatRect textBounds() const;
XAlignment textXAlignment() const;
YAlignment textYAlignment() const;
sf::Texture* texturePtr() const;
bool visible() const;
ClickCallback onClick() const;
const Frame* getFirstChild() const;
const Frame* getNextSibling() const;
const Frame* getChildByID(std::string id) const;
sf::Text& getSFText();

// Setters
Frame* position(const UIDimensions& pos);
Frame* size(const UIDimensions& sz);
Frame* anchor(const sf::Vector2f& an);
Frame* padding(const Padding& pd);
Frame* bgColor(const sf::Color& color);
Frame* outlineColor(const sf::Color& color);
Frame* outlineThickness(const float& thickness);
Frame* text(const std::string& str);
Frame* text(const std::string& str, const sf::Font& fnt, unsigned int chSz);
Frame* font(const sf::Font& fnt);
Frame* characterSize(unsigned int chSz);
Frame* textStyle(std::uint32_t style);
Frame* textColor(const sf::Color& color);
Frame* textOutlineColor (const sf::Color& color);
Frame* textOutlineThickness(float thickness);
Frame* textXAlignment(const XAlignment& alignment);
Frame* textYAlignment(const YAlignment& alignment);
Frame* texturePtr(sf::Texture* tex);
Frame* visible(bool v);
Frame* onClick(ClickCallback fn);

// Makes the frame the child of the argument.
Frame* appendTo(Frame* other);

// Makes the argument frame the current frame's child. Returns the argument frame.
Frame* append(Frame* other);

Frame* editFirstChild();
Frame* editNextSibling();
Frame* editChildByID(const std::string& id);
```