#pragma once

#include "GAnimation.h"
#include "GSprite.h"
#include "GObject.h"
#include <list>
using namespace std;

class Ground:public GObject
{
public:
	bool	isBright;
	
	Ground();
	Ground(float _x, float _y,float width,float height,bool _isBright,int _ID,GSprite* _sprite);
	void Render(GCamera *camera);
	void ResetWhenReload(GSprite* _sprite);
	void Save(fstream *fs);
	void Load(fstream *fs);
};