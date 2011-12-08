#pragma once
#include "GObject.h"
#include "GSprite.h"
#include "GAnimation.h"
#include <list>

using namespace std;
class Mario;
class Bullet :	public GObject
{
private: 
	float vx;
	float vy;
	float ay;
	float xOld;
	float yOld;
	float timedelay;
	float timeblow;
	RECT oldRect;
	bool isNeedDelete;
	list<GObject*>* collisionList;
	GSprite* sprite1;//explosion
	Mario* mario;
public:
	char state;
	Bullet(void);
	~Bullet(void);
	Bullet(float _x,float _y,float width,float height,float _vx,GSprite* _sprite,GSprite* _sprite1);
	void Update(list<GObject*>* staObjs,list<GObject*>* dynObjs,GInput* input, float TPF);
	void Render(GCamera* camera);	
	void Move(float TPF,list<GObject*>* staObjs,list<GObject*>* dynObjs);
	void ChangeState(char _state);
	void SetVar(char* varName,int val);
	int GetVar(char* varName);
};
