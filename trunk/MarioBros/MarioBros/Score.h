#pragma once

#include "GAnimation.h"
#include "GSprite.h"
#include "GObject.h"
#include <list>
using namespace std;

class Score:public GObject
{
public:
	float	distanceMove;
	float	vy;
	bool	isNeedDelete;
	int		score;

	Score();
	Score(GSprite* _sprite,float _x,float _y,int _score);
	void Update(float TPF);
	void Render(GCamera* camera);
	int	GetVar(char* varName);
};