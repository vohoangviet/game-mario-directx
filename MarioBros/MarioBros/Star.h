#pragma once

#include "GAnimation.h"
#include "GSprite.h"
#include "GObject.h"
#include <list>
using namespace std;

//Là nấm khi Mario còn nhỏ, nếu Mario lớn rồi thì nó là hoa.
class Star:public GObject
{
private:
	bool	isCheckedContainer;
	list<GObject*>*	collisionList;
	float vx;
	float vy;
	float ay;
	float xOld;
	float yOld;
	RECT	oldRect;
	bool	isNeedDelete;
public:
	GObject* container;
	char	state;

	Star();
	Star(float _x, float _y,float width,float height,int _ID,GSprite* _sprite);
	~Star();
	void Update(list<GObject*>* staObjs,list<GObject*>* dynObjs,GInput* input, float TPF);
	void Render(GCamera* camera);
	void CheckObjects(list<GObject*>* staObjs);
	void Move(float TPF,list<GObject*>* staObjs,list<GObject*>* dynObjs);
	void ChangeState(char _state);
	void SetVar(char* varName,int val);
	int GetVar(char* varName);
	void ResetWhenReload(GSprite* _sprite);
	void Save(fstream *fs);
	void Load(fstream *fs);
};