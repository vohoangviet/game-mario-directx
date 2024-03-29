#include "Flag.h"
#include "GObject.h"
#include "Info.h"
#include "GAnimation.h"
#include "GSprite.h"

Flag::Flag():GObject(){}
Flag::Flag(float _x, float _y,float width,float height,int _ID,GSprite* _sprite):GObject(_x,_y,width,height)
{
	sprite		=_sprite;
	ID			=_ID;
	yFlag		=y+TILE_SIZE;
	state		=TS_IDLE;
	ani			=new GAnimation(2,2,0,sprite);
	ResetRect();
}
void Flag::Update(list<GObject*>* staObjs,list<GObject*>* dynObjs,GInput* input, float TPF)
{
	if(state==TS_ACTIVING)
	{
		yFlag+=200*TPF;							//Cập nhật tọa độ cờ.
		if(yFlag>y+TILE_SIZE*9)
		{
			yFlag=y+TILE_SIZE*9;
			ChangeState(TS_IDLE_2);
		}
	}
}
void Flag::ChangeState(char _state)
{
	state=_state;
}
void Flag::Render(GCamera *camera)
{
	sprite->Draw(x+TILE_SIZE-camera->x,y,ZOOM,ZOOM,ani->GetRect(1),0.5);
	sprite->Draw(x+TILE_SIZE/2-camera->x,yFlag,ZOOM,ZOOM,ani->GetRect(2),0.5);	//Cờ
	for(char i=1;i<10;i++)
		sprite->Draw(x+TILE_SIZE-camera->x,y+i*TILE_SIZE,ZOOM,ZOOM,ani->GetRect(5),0.5);
	sprite->Draw(x+TILE_SIZE-camera->x,y+10*TILE_SIZE,ZOOM,ZOOM,ani->GetRect(0),0.5);	//Chân
}
void Flag::ResetWhenReload(GSprite* _sprite)
{
	sprite=_sprite;
	ani=new GAnimation(2,2,0,sprite);
}
void Flag::Save(fstream *fs)
{
	fs->write(reinterpret_cast<char*>(&ID),sizeof(ID));	//int ID, để khi load biết được đang load Obj nào
	int sizeObj=sizeof(*this);
	fs->write(reinterpret_cast<char*>(&sizeObj),sizeof(int));			//int sizeof(obj)
	fs->write(reinterpret_cast<char*>(this),sizeObj);
}
void Flag::Load(fstream *fs)
{
	int sizeObj;
	fs->read(reinterpret_cast<char*>(&sizeObj),sizeof(int));			//int sizeof(obj)
	fs->read(reinterpret_cast<char*>(this),sizeObj);
}
void Flag::ResetRect()
{
	rect.left=x+TILE_SIZE;
	rect.right=rect.left+TILE_SIZE;
	rect.top=y+10*TILE_SIZE;
	rect.bottom=rect.top+TILE_SIZE;
}
void Flag::SetVar(char* varName,int val)
{
	if(strcmp(varName,"state")==0)
		ChangeState(val);
}
int Flag::GetVar(char* varName)
{
	if(strcmp(varName,"state")==0)
		return state;
	return -1;
}