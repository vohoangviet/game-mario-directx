#include "Stone.h"
#include "GObject.h"
#include "Info.h"
#include "GAnimation.h"
#include "GSprite.h"

Stone::Stone():GObject(){}
Stone::Stone(float _x, float _y,float width,float height,bool _isBright,int _ID,GSprite* _sprite):GObject(_x,_y,width,height)
{
	isBright	=_isBright;
	sprite		=_sprite;
	ID			=_ID;	
	ani			=new GAnimation(4,4,0.5,sprite);
}
void Stone::Render(GCamera *camera)
{
	if(isBright)
		sprite->Draw(x-camera->x,y,ZOOM,ZOOM,ani->GetRect(2),0.5);
	else sprite->Draw(x-camera->x,y,ZOOM,ZOOM,ani->GetRect(6),0.5);
}
void Stone::ResetWhenReload(GSprite* _sprite)
{
	sprite=_sprite;
	ani=new GAnimation(4,4,0.5,sprite);
}
void Stone::Save(fstream *fs)
{
	fs->write(reinterpret_cast<char*>(&ID),sizeof(ID));	//int ID, để khi load biết được đang load Obj nào
	int sizeObj=sizeof(*this);
	fs->write(reinterpret_cast<char*>(&sizeObj),sizeof(int));			//int sizeof(obj)
	fs->write(reinterpret_cast<char*>(this),sizeObj);
}
void Stone::Load(fstream *fs)
{
	int sizeObj;
	fs->read(reinterpret_cast<char*>(&sizeObj),sizeof(int));			//int sizeof(obj)
	fs->read(reinterpret_cast<char*>(this),sizeObj);
}