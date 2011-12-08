#pragma once

#include "GAnimation.h"
#include "GSprite.h"
#include "GObject.h"
#include <list>
using namespace std;

class Castle:public GObject
{
public:
	Castle();
	Castle(float _x, float _y,float width,float height,int _ID,GSprite* _sprite);
	void Render(GCamera *camera);
	void ResetRect();
	void ResetWhenReload(GSprite* _sprite);
	void Save(fstream *fs);
	void Load(fstream *fs);
	
};