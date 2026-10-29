# cenui
Crude SFML UI library whipped up in a week to support my group's university project.

**A disclaimer to all who would use:**
The ultra-simple API and integration with sfml might be appealing. But know what
you are using before you use it. This is a very basic, hastily made UI library
that I wrote, not because I wanted to compete with dear imgui, but because my
team on a school project needed an ultra simple but customizable UI library for
our project.

This library is held together not by stellar programming but by luck. It is not
battle tested. Good thing is if something breaks the codebase is like 500 lines
total so you shouldn't have too hard of a time fixing it up yourself if need be.

**KNOWN ISSUES:**
- If frame A is a button with non-button sibling B, and B is drawn above A, then when the mouse clicks the region occupied by both A and B, a click is registered for A even though it should be covered by B.
