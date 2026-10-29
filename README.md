# cenui
Ugly crude SFML UI library whipped up in two days to support my group's university project.

KNOWN ISSUES:
- If frame A is a button with non-button sibling B, and B is drawn above A, then when the mouse clicks the region occupied by both A and B, a click is registered for A even though it should be covered by B.
