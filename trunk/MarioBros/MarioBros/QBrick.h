#pragma once

#include "GAnimation.h"
#include "GSprite.h"
#include "GObject.h"
#include <list>
using namespace std;

class QBrick:public GObject
{
private:
	char	state;
	float	vy;
	float	ay;
	float	yOld;
public:
	bool	isChanged;
	bool	isBright;

	QBrick();
	QBrick(float _x, float _y,float width,float height,bool _isBright,int _ID,GSprite* _sprite);
	void Update(list<GObject*>* staObjs,list<GObject*>* dynObjs,GInput* input, float TPF);
	void SetVar(char* varName,int val);
	int GetVar(char* varName);
	void Render(GCamera *camera);
	void ChangeState(char _state);
	void UpdateAnimation(float TPF);
	void ResetWhenReload(GSprite* _sprite);
	void Save(fstream *fs);
	void Load(fstream *fs);
};