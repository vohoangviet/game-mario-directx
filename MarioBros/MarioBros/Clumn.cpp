#include "Clumn.h"
#include "GObject.h"
#include "Info.h"
#include "GAnimation.h"
#include "GSprite.h"

Clumn::Clumn():GObject(){}
Clumn::Clumn(float _x, float _y,float width,float height,int _ID,GSprite* _sprite):GObject(_x,_y,width,height)
{
	sprite	=_sprite;
	ID	=_ID;	
	ani=new GAnimation(4,5,0,sprite);
}
void Clumn::Render(GCamera* camera)
{
	sprite->Draw(x-camera->x,y,ZOOM,ZOOM,ani->GetRect(12),1.0);
	switch(ID)
	{
	case 13:						//Clumn 1
		sprite->Draw(x+TILE_SIZE-camera->x,y,ZOOM,ZOOM,ani->GetRect(14),1.0);
		break;
	case 14:						//Clumn 2
		sprite->Draw(x+TILE_SIZE-camera->x,y,ZOOM,ZOOM,ani->GetRect(13),1.0);
		sprite->Draw(x+2*TILE_SIZE-camera->x,y,ZOOM,ZOOM,ani->GetRect(14),1.0);
		break;
	case 15:
		sprite->Draw(x+TILE_SIZE-camera->x,y,ZOOM,ZOOM,ani->GetRect(13),1.0);
		sprite->Draw(x+2*TILE_SIZE-camera->x,y,ZOOM,ZOOM,ani->GetRect(13),1.0);
		sprite->Draw(x+3*TILE_SIZE-camera->x,y,ZOOM,ZOOM,ani->GetRect(14),1.0);
		break;
	}
}
void Clumn::ResetWhenReload(GSprite* _sprite)
{
	sprite=_sprite;
	ani=new GAnimation(4,5,0,sprite);	
}
void Clumn::Save(fstream *fs)
{
	fs->write(reinterpret_cast<char*>(&ID),sizeof(ID));	//int ID, để khi load biết được đang load Obj nào
	int sizeObj=sizeof(*this);
	fs->write(reinterpret_cast<char*>(&sizeObj),sizeof(int));			//int sizeof(obj)
	fs->write(reinterpret_cast<char*>(this),sizeObj);
}
void Clumn::Load(fstream *fs)
{
	int sizeObj;
	fs->read(reinterpret_cast<char*>(&sizeObj),sizeof(int));			//int sizeof(obj)
	fs->read(reinterpret_cast<char*>(this),sizeObj);
}