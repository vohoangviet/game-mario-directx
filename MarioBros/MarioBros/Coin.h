#pragma once

#include "GAnimation.h"
#include "GSprite.h"
#include "GObject.h"
#include <list>
using namespace std;

class Coin:public GObject
{
private:

	float	yTemp;
	float	vy;
	float	ay;

	GObject* container;
	bool	isCheckedContainer;
	bool	isNeedDelete;
	void CheckContainer(list<GObject*>* staObjs);
public:
	char	state;
	int	numCoin;

	Coin();
	Coin(float _x, float _y,float width,float height,int _ID,GSprite* _sprite);
	void Update(list<GObject*>* staObjs,list<GObject*>* dynObjs,GInput* input, float TPF);
	void Render(GCamera* camera);
	void ChangeState(char _state);
	void SetVar(char* varName,int val);
	int GetVar(char* varName);
	void ResetWhenReload(GSprite* _sprite);
	void ResetRect();
	void Save(fstream *fs);
	void Load(fstream *fs);
};