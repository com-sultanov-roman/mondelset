#pragma once
#include "common.h"
#include <vector>

class Drawable
{
public:
	virtual void draw();
};

class node {
	char* name;
	int level;
	vector<Drawable *> children;

};

class GraphScene {

};

