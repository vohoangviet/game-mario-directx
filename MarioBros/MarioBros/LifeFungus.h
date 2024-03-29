#pragma once

#include "GAnimation.h"
#include "GSprite.h"
#include "GObject.h"
#include <list>
using namespace std;

//Là nấm khi Mario còn nhỏ, nếu Mario lớn rồi thì nó là hoa.
class LifeFungus:public GObject
{
private:
	bool	isCheckedContainer;
	list<GObject*>* collisionList;
public:

	float	vx;
	float	vy;
	float	ay;
	float	xOld;
	float	yOld;
	char	state;
	RECT	oldRect;
	bool	isNeedDelete;

	GObject* container;

	LifeFungus();
	LifeFungus(float _x, float _y,float width,float height,int _ID,GSprite* _sprite);
	~LifeFungus();
	void Update(list<GObject*>* staObjs,list<GObject*>* dynObjs,GInput* input, float TPF);
	void ChangeState(char _state);
	void CheckObjects(list<GObject*>* staObjs);
	void Move(float TPF,list<GObject*>* staObjs,list<GObject*>* dynObjs);
	void Render(GCamera* camera);

	void SetVar(char* varName,int val);
	int GetVar(char* varName);
	void ResetWhenReload(GSprite* _sprite);
	void Save(fstream *fs);
	void Load(fstream *fs);
};

