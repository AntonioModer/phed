## Description ##

Phed is an open source cross-platform map editor with a built-in physics simulator, written in C++. It uses Qt (Nokia) for the GUI, and Box2D (Erin Catto) for physics. It is being developed by Mark Bayazit.

## Screenshot ##

<img src='http://img443.imageshack.us/img443/7453/phed2.png' />

## Videos ##

<a href='http://www.youtube.com/watch?feature=player_embedded&v=tGpHvrssMIU' target='_blank'><img src='http://img.youtube.com/vi/tGpHvrssMIU/0.jpg' width='425' height=344 /></a>

<a href='http://www.youtube.com/watch?feature=player_embedded&v=XDpx5sP2FRA' target='_blank'><img src='http://img.youtube.com/vi/XDpx5sP2FRA/0.jpg' width='425' height=344 /></a>

This isn't directly from the editor, but someone used a rag-doll I created for this project and tossed him down some stairs. Poor guy!

## Current Features ##

  * Support for non-convex and clockwise polygons (not natively supported by Box2D)
  * All Box2D properties are editable (friction, restitution, etc.)
  * Cross-platform

## Planned Features ##

  * Edge chains
  * Freehand shape drawing
  * Moving/rotating objects
  * Joints (lots!)
  * Minimap
  * History (undo)
  * Textures
  * Presets and premade objects
  * Loading/saving

## Warning ##

This was tested on Ubuntu 9.04 and 9.10. The breakable polygons feature is highly unstable; use at your own risk (will crash). This project is in its very early stages, and is better used as a point of reference than a useful program.

## Building ##

Tested on Qt4.5, <a href='http://code.google.com/p/box2d/'>Box2D</a> rev10, Ubuntu 9.04 64-bit. Built using <a href='http://bits.netbeans.org/netbeans/6.8/m1/'>NetBeans 6.8m1</a> (Aug 2, 2009).

There's a Makefile that might work...