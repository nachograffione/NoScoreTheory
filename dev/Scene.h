#ifndef SCENE_H
#define SCENE_H
#include "MainView.h"

//forward declaration
class MainView;

class Scene {
public:
	virtual void handler(MainView &mainV) = 0;
	virtual void draw(MainView &mainV) = 0;
	virtual void afterDisplay() = 0;
	
};

#endif

