#pragma once

#include "GAnimation.h"
#include "GSprite.h"
#include "GObject.h"
#include <list>
using namespace std;

//Là nấm khi Mario còn nhỏ, nếu Mario lớn rồi thì nó là hoa.
class PowerUp:public GObject
{
public:
	GObject* container;
	float	vx;
	float	vy;
	float	ay;
	float	xOld;
	float	yOld;
	char	state;
	bool	isFungus;
	bool	isCheckedContainer;
	bool	isNeedDelete;

	PowerUp();
	PowerUp(float _x, float _y,float width,float height,int _ID,GSprite* _sprite);
	void Update(list<GObject*>* staObjs,list<GObject*>* dynObjs,GInput* input, float TPF);
	void CheckObjects(list<GObject*>* staObjs,list<GObject*>* dynObjs);
	void ChangeState(int _state);
	void Move(float TPF,list<GObject*>* staObjs,list<GObject*>* dynObjs);
	void Render(GCamera* camera);
	void UpdateAnimation(float TPF);
	void SetVar(char* varName,int val);
	int GetVar(char* varName);
	void ResetWhenReload(GSprite* _sprite);
	void Save(fstream *fs);
	void Load(fstream *fs);
};