#pragma once

#include "GAnimation.h"
#include "GSprite.h"
#include "GObject.h"
#include <list>
using namespace std;

class Flag:public GObject
{
private:
	float yFlag;
	char state;
public:
	Flag();
	Flag(float _x, float _y,float width,float height,int _ID,GSprite* _sprite);
	void Update(list<GObject*>* staObjs,list<GObject*>* dynObjs,GInput* input, float TPF);
	void Render(GCamera *camera);
	void ResetWhenReload(GSprite* _sprite);
	void ChangeState(char _state);
	void SetVar(char* varName,int val);
	int GetVar(char* varName);
	void Save(fstream *fs);
	void Load(fstream *fs);
	void ResetRect();
};