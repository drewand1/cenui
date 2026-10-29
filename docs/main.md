# cenui Documentation

## Building and linking
cenui is a static library that links with statically built sfml. How to build
with cenui: add it as a CMake subdirectory. Do not make it more complicated; it
might make it freak out.

## Hello World
Very basic example that displays one frame with a button in the middle:
```c++
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cenui.h>
#include <iostream>

void clickCallback(cenui::Frame* clickedFrame) {
	std::cout << "Hello world!" << std::endl;
}

int main() {
	sf::Font font("determination.ttf");
	sf::RenderWindow window(sf::VideoMode({800, 600}), "test1");
	cenui::FrameManager frameMgr;

	cenui::Frame* panel = frameMgr.root()->append(new cenui::Frame("panel"))
		->anchor({0.5f, 0.5f})
		->position({{0.5f, 0.5f}, {0, 0}})
		->size({{0, 0}, {400, 300}});

	cenui::Frame* button = panel->append(new cenui::Frame("button"))
		->anchor({0.5f, 0.5f})
		->position({{0.5f, 0.5f}, {0, 0}})
		->size({{0, 0}, {200, 100}})
		->text("Click me!")
		->font(font)
		->characterSize(16u)
		->bgColor({200, 255, 200, 255})
		->onClick(clickCallback);

	while (window.isOpen()) {
		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}

			if (const auto* resized = event->getIf<sf::Event::Resized>()) {
				sf::FloatRect newView({100.0f, 100.0f}, sf::Vector2f(resized->size));
				window.setView(sf::View(newView));
			}

			if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
				if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
					frameMgr.handleMouseDown(window);
				}
			}

			if (const auto* mouseButtonReleased = event->getIf<sf::Event::MouseButtonReleased>()) {
				if (mouseButtonReleased->button == sf::Mouse::Button::Left) {
					frameMgr.handleMouseUp(window);
				}
			}
		}

		window.clear(sf::Color::Black);
		frameMgr.drawFrames(window);
		window.display();
	}

	return 0;
}
```

From this example you can pretty much learn everything about this library.

### FrameManager
The FrameManager is the container class for all of your application's UI. This
FrameManager exposes a root frame that you can append all new frames to and a
few methods:
- `cenui::Frame* root()`: returns the root frame for you to use.
- `void drawFrames(sf::RenderWindow& w)`: draws all frames descending from root. Call this after everything else so that your UI overlaps your main content (e.g. a game or something).
- `void handleMouseDown(const sf::RenderWindow& w)`: handles the mouse down event. Throw that in the usual SFML event loop.
- `void handleMouseUp(const sf::RenderWindow& w)`: handles the mouse up event. Throw that in the usual SFML event loop.

The last two have to do with detecting clicks on frames. If you're sure you
won't set an onClick callback for any of your frames, you don't have to call
those.

### Frames
A cenui [Frame](api/frame.md) is a class that represents one UI element. Here's the general form
for how to create one:
```c++
cenui::Frame* frame = parentFrame->append("Frame ID")
	->propertyName(propertyValue)
	->anotherPropertyName(anotherPropertyValue);
```
Take a parent frame, call `append` with the frame ID, then use the setter
methods to set properties.

The convention for getters and setters is as follows: for any property `prop` of
type `T` that can be both gotten and set, `Frame` will provide two overloaded
methods:
- **Getter:** `T prop() const;`
- **Setter:** `Frame* prop(T arg) const;`, which `this`, meaning you can chain
them together as in the example.

Using `append` makes the created frame a *child frame* to the parent. This means
two things:
1. The new frame will be positioned and sized relative to the parent. A position
of {{0, 0}, {10, 10}} means 10 pixels away from the top left corner of the
*parent frame*, not the window.
2. The new frame ID may not have the same ID as any other immediate child under
the parent. Further descendants of the parent (e.g. the child of a sibling
frame may have the same id as the new frame).

You can use the `onClick` setter with argument of type `void(*)(cenui::Frame*)`
to set the callback for when the frame is clicked to the argument function. The
frame that was clicked will be passed as the argument to the callback.

To run this example, you'll need a font file. As you can see, this example uses
determination.ttf. Either get that one or use your own and drop it into the same
folder as your executable.

**WARNING:** In the destructor method, frames are dynamically freed using
`delete`. You must, then, allocate frames with `new`. Non-heap-allocated frames
causes undefined behavior and will probably crash your program.

### UIDimensions (positioning and sizing)
Frames are positioned and sized using the [UIDimensions](api/uidimensions.md)
struct, which contains two `sf::Vector2f`s: `scale` and `offset`. `scale` is a
fraction of the parent's size. `offset` is a raw pixel offset added onto the
absolute size or position after the scale is applied. It can be constructed with
a literal of the following form: `{{scaleX, scaleY}, {offsetX, offsetY}}`. A
UIDimensions `{{0.5f, 0.5f}, {-50, 20}}` means half of the parent on each axis,
minus 50px on the x axis, plus 20px on the y axis.

## Gotchas
There are a few quirks that come with the fact that this library was thrown
together in a week as a tool to support another project with very simple UI
demands and thus the library runs not on C++ but on hopes and prayers. Here are
a few things you should keep in mind:
- The draw order of child frames is set in stone. Children appended later will
be drawn above children appended before. There is no way to change the order
except for planning ahead and appending child frames in the order you want.
- The frame has an `emancipate` method that removes it from its parent. It is
not yet implemented. There is no way to remove a frame from child-ship of its
parent. Furthermore, calling `appendTo` on a frame when it already has a parent
will cause problems.
