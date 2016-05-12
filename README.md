Cassave Engine
==============

Cassave is a small game engine, originally created for web-based games, that implements
an Entity/Component/System framework and uses the V8 Javascript engine for scripting
duties. Since it was originally created for HTML5/JS game engine research, I've been
toying with the idea that the same game codebase I was writing for the HTML5/JS engine
could also be executed in a native engine implementation. Write once using a single JS
API for Graphics/Physics/Sound systems and deploy to web and native desktop engine
clients.


ROADMAP
-------

Right now it's barely a real interpreter, let alone an engine. In the momment the module system 
is being written. Basically it will be a stripped-down version of node.js's module system. After
that the basic internal library will be written (GLFW, GLM and Box2d bindings).


Dependencies
------------

- v8
- c++14 able compiler

Building
--------

todo: finish this section 
