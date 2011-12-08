#pragma once

#include "GAnimation.h"
#include "GSprite.h"
#include "GObject.h"
#include <list>
using namespace std;

class Sign:public GObject
{
public:
	Sign();
	Sign(float _x, float _y,float width,float height,int _ID);
	void Save(fstream *fs);
	void Load(fstream *fs);
};