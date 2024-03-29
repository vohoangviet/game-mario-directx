#pragma once

#include "GAnimation.h"
#include "GSprite.h"
#include "GObject.h"
#include <list>
using namespace std;

class Koopa:public GObject
{
private:
	list<GObject*>* collisionList;
	RECT	oldRect;
public:
	float	vx;
	float	vy;
	float	ay;
	float	xOld;
	float	yOld;
	float	waitIdle;

	bool	isBright;
	bool	isNeedDelete;
	char	state;

	Koopa();
	Koopa(float _x, float _y,float width,float height,bool _isBright,int _ID,GSprite* _sprite,Game* _game);
	~Koopa();
	void Update(list<GObject*>* staObjs,list<GObject*>* dynObjs,GInput* input, float TPF);
	void Render(GCamera* camera);
	void Move(float TPF,list<GObject*>* staObjs);
	void UpdateAnimation(float TPF);
	void ChangeState(char _state);
	int GetVar(char* varName);
	void SetVar(char* varName,int val);
	void ResetRect();
	void ResetWhenReload(GSprite* _sprite);
	void Save(fstream *fs);
	void Load(fstream *fs);
};