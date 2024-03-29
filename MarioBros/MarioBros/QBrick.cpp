#include "QBrick.h"
#include "GObject.h"
#include "Info.h"
#include "GAnimation.h"
#include "GSprite.h"

QBrick::QBrick():GObject(){}
QBrick::QBrick(float _x, float _y,float width,float height,bool _isBright,int _ID,GSprite* _sprite):GObject(_x,_y,width,height)
{
	sprite		=_sprite;
	ID			=_ID;
	isChanged	=false;
	isBright	=_isBright;
	state		=TS_IDLE;
	yOld		=y;
	ani			=new GAnimation(4,4,0.5,sprite);
}
void QBrick::Update(list<GObject*>* staObjs,list<GObject*>* dynObjs,GInput *input, float TPF)
{
	if(state==TS_MOVEUP)
	{
		vy+=ay*TPF;
		y+=vy*TPF+1/2*ay*TPF*TPF;
		if(y>yOld)
			ChangeState(TS_IDLE_2);
	}
	UpdateAnimation(TPF);
}
void QBrick::UpdateAnimation(float TPF)
{
	if(!isChanged)
	{
		if(ani->index==8)
			ani->timePerImage=0.7;
		else ani->timePerImage=0.2;
		ani->Update(8,10,TPF);
	}
	else if(isBright) ani->SetIndex(3);
	else ani->SetIndex(7);
}
void QBrick::ChangeState(char _state)
{
	state=_state;
	switch(state)
	{
	case TS_IDLE: case TS_IDLE_2:
		y=yOld;
		vy=0;
		ay=0;
	case TS_MOVEUP:
		vy=-200;
		ay=G;
		break;
	}
}
void QBrick::Render(GCamera *camera)
{
	sprite->Draw(x-camera->x,y,ZOOM,ZOOM,ani->rect,0.5);
}
void QBrick::SetVar(char* varName,int val)
{
	if(strcmp(varName,"isChanged")==0)
	{
		if(val==0)
			isChanged=false;
		else isChanged=true;
		return;
	}
	if(strcmp(varName,"state")==0)
	{
		ChangeState(val);
		return;
	}
}
int QBrick::GetVar(char* varName)
{
	if(strcmp(varName,"isChanged")==0)
		return isChanged;
	if(strcmp(varName,"state")==0)
		return state;
	return -1;
}
void QBrick::ResetWhenReload(GSprite* _sprite)
{
	sprite=_sprite;
	ani=new GAnimation(4,4,0.5,sprite);
}
void QBrick::Save(fstream *fs)
{
	fs->write(reinterpret_cast<char*>(&ID),sizeof(ID));	//int ID, để khi load biết được đang load Obj nào
	int sizeObj=sizeof(*this);
	fs->write(reinterpret_cast<char*>(&sizeObj),sizeof(int));			//int sizeof(obj)
	fs->write(reinterpret_cast<char*>(this),sizeObj);
}
void QBrick::Load(fstream *fs)
{
	int sizeObj;
	fs->read(reinterpret_cast<char*>(&sizeObj),sizeof(int));			//int sizeof(obj)
	fs->read(reinterpret_cast<char*>(this),sizeObj);
}