#include "Cloud.h"
#include "GObject.h"
#include "Info.h"
#include "GAnimation.h"
#include "GSprite.h"

Cloud::Cloud():GObject(){}
Cloud::Cloud(float _x, float _y,float width,float height,int _ID,GSprite* _sprite):GObject(_x,_y,width,height)
{
	sprite	=_sprite;
	ID	=_ID;	
	ani=new GAnimation(4,5,0,sprite);
}
void Cloud::Render(GCamera* camera)
{
	RECT r={0,16,16,32};
	sprite->Draw(x-camera->x,y,ZOOM,ZOOM,ani->GetRect(4),1.0);
	sprite->Draw(x-camera->x,y+TILE_SIZE,ZOOM,ZOOM,ani->GetRect(8),1.0);
	switch(ID)
	{
	case 10:						//Cloud 1
		sprite->Draw(x+TILE_SIZE-camera->x,y,ZOOM,ZOOM,ani->GetRect(6),1.0);
		sprite->Draw(x+TILE_SIZE-camera->x,y+TILE_SIZE,ZOOM,ZOOM,ani->GetRect(10),1.0);
		break;
	case 11:						//Cloud 2
		sprite->Draw(x+TILE_SIZE-camera->x,y,ZOOM,ZOOM,ani->GetRect(5),1.0);
		sprite->Draw(x+TILE_SIZE-camera->x,y+TILE_SIZE,ZOOM,ZOOM,ani->GetRect(9),1.0);
		sprite->Draw(x+2*TILE_SIZE-camera->x,y,ZOOM,ZOOM,ani->GetRect(6),1.0);
		sprite->Draw(x+2*TILE_SIZE-camera->x,y+TILE_SIZE,ZOOM,ZOOM,ani->GetRect(10),1.0);
		break;
	case 12:
		sprite->Draw(x+TILE_SIZE-camera->x,y,ZOOM,ZOOM,ani->GetRect(5),1.0);
		sprite->Draw(x+TILE_SIZE-camera->x,y+TILE_SIZE,ZOOM,ZOOM,ani->GetRect(9),1.0);
		sprite->Draw(x+2*TILE_SIZE-camera->x,y,ZOOM,ZOOM,ani->GetRect(5),1.0);
		sprite->Draw(x+2*TILE_SIZE-camera->x,y+TILE_SIZE,ZOOM,ZOOM,ani->GetRect(9),1.0);
		sprite->Draw(x+3*TILE_SIZE-camera->x,y,ZOOM,ZOOM,ani->GetRect(6),1.0);
		sprite->Draw(x+3*TILE_SIZE-camera->x,y+TILE_SIZE,ZOOM,ZOOM,ani->GetRect(10),1.0);
		break;
	}
}
void Cloud::ResetWhenReload(GSprite* _sprite)
{
	sprite=_sprite;
	ani=new GAnimation(4,5,0,sprite);
}
void Cloud::Save(fstream *fs)
{
	fs->write(reinterpret_cast<char*>(&ID),sizeof(ID));	//int ID, để khi load biết được đang load Obj nào
	int sizeObj=sizeof(*this);
	fs->write(reinterpret_cast<char*>(&sizeObj),sizeof(int));			//int sizeof(obj)
	fs->write(reinterpret_cast<char*>(this),sizeObj);
}
void Cloud::Load(fstream *fs)
{
	int sizeObj;
	fs->read(reinterpret_cast<char*>(&sizeObj),sizeof(int));			//int sizeof(obj)
	fs->read(reinterpret_cast<char*>(this),sizeObj);
}