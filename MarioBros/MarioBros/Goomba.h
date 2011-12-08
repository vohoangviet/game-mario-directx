#pragma once

#include "GAnimation.h"
#include "GSprite.h"
#include "GObject.h"
#include <list>
using namespace std;

class Goomba:public GObject
{
private:
	list<GObject*>* collisionList;
	RECT	oldRect;
public:
	bool	isBright;
	bool	isAlive;

	float	xOld;
	float	yOld;
	float	vx;
	float	vy;
	float	ay;

	char	state;
	bool	isNeedDelete;
	float	waitIdle;
	Game*	game;

	Goomba();
	Goomba(float _x, float _y,float width,float height,bool _isBright,int _ID,GSprite* _sprite,Game* _game);
	~Goomba();
	void Update(list<GObject*>* staObjs,list<GObject*>* dynObjs,GInput* input, float TPF);
	void Move(float TPF,list<GObject*>* staObjs);
	void UpdateAnimation(float TPF);
	void Render(GCamera* camera);
	void ChangeState(char _state);
	void SetVar(char* varName,int val);
	int GetVar(char* varName);
	void ResetWhenReload(GSprite* _sprite);
	void Save(fstream *fs);
	void Load(fstream *fs);
};