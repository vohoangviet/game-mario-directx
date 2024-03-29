#pragma once

#include "GAnimation.h"
#include "GSprite.h"
#include "GObject.h"
#include <list>
using namespace std;

class Brick:public GObject
{
private:
	char	state;
	float	yOld;
	float	vy;
	float	ay;
	float	xBreak1;		//Tham số của các mảnh vỡ. 1 là mảnh trên, 2 là mảnh dưới
	float	yBreak1;
	float	xBreak2;
	float	yBreak2;
	float	vyBreak1;
	float	vyBreak2;
	float	vxBreak1;
	float	vxBreak2;
	float	ayBreak;
	float	angle;
	bool	isContainCoin;
public:
	bool	isBright;
	bool	isNeedDelete;
	bool	isChanged;

	Brick();
	Brick(float _x, float _y,float width,float height,bool _isBright,int _ID,GSprite* _sprite);
	void SetVar(char* varName,int val);
	int GetVar(char* varName);
	void Update(list<GObject*>* staObjs,list<GObject*>* dynObjs,GInput* input, float TPF);
	void Render(GCamera *camera);
	void ChangeState(char _state);
	void ResetWhenReload(GSprite* _sprite);
	void Save(fstream *fs);
	void Load(fstream *fs);
};