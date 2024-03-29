#include "Coin.h"
#include "GObject.h"
#include "Info.h"
#include "GAnimation.h"
#include "GSprite.h"
#include "GCollision.h"
#include "Brick.h"
#include "QBrick.h"

Coin::Coin():GObject(){}
Coin::Coin(float _x, float _y,float width,float height,int _ID,GSprite* _sprite):GObject(_x,_y,width,height)
{
	sprite	=_sprite;
	ID	=_ID;
	ani=new GAnimation(4,5,0.2,sprite);

	container=NULL;
	isCheckedContainer	=false;
	state	=IS_FREE;
	numCoin	=1;
	isNeedDelete	=false;
	ResetRect();
}
void Coin::Update(list<GObject*>* staObjs,list<GObject*>* dynObjs,GInput* input, float TPF)
{
	CheckContainer(staObjs); 

	switch(state)
	{
	case IS_IDLE:
		if(numCoin==0)
			ChangeState(IS_ATE);
		break;
	case IS_FREE:							//Không bị chứa
		ani->Update(12,14,TPF);
		break;
	case IS_ACTIVING:						//Đang nảy lên
		if(numCoin==0)
			if(container!=NULL)
				container->SetVar("isChanged",true);
		vy+=ay*TPF;
		yTemp+=vy*TPF+0.5*ay*TPF*TPF;
		if(yTemp>y-TILE_SIZE*2&&vy>0)		
			ChangeState(IS_IDLE);
		ani->Update(16,20,TPF);
		break;
	}
}
void Coin::CheckContainer(list<GObject*>* staObjs)
{
	if(isCheckedContainer==true) return;

	list<GObject*>::iterator i;
	GObject* obj;
	for(i=staObjs->begin();i!=staObjs->end();i++)
	{
		obj=*i;
		if(obj->ID==24||obj->ID==25)
			if(GCollision::RectVsRect(rect,obj->rect))
			{
				container=obj;
				state=IS_IDLE;
				if(obj->ID==24)			//Nếu tiền nằm trong gạch
				{
					numCoin=5;
					obj->SetVar("isContainCoin",true);
				}
			}
	}
	isCheckedContainer=true;
}
void Coin::Render(GCamera* camera)
{
	if(state!=IS_IDLE&&state!=IS_ATE)
	{
		if(state==IS_FREE)
			sprite->Draw(x-camera->x,y,ZOOM,ZOOM,ani->rect,0.75);
		else if(state==IS_ACTIVING&&ani->index!=0)
			sprite->Draw(x-camera->x,yTemp,ZOOM,ZOOM,ani->rect,0.75);
	}
}
void Coin::ChangeState(char _state)
{
	state=_state;
	switch(state)
	{
	case IS_IDLE:
		state=IS_IDLE;
		ani->SetIndex(16);
		break;
	case IS_ACTIVING:
		yTemp=y-TILE_SIZE;
		vy=-800;
		ay=G;
		break;
	case IS_ATE:
		isNeedDelete=true;
		break;
	}
}
int Coin::GetVar(char* varName)
{
	if(strcmp(varName,"isNeedDelete")==0)
		return isNeedDelete;
	if(strcmp(varName,"numCoin")==0)
		return numCoin;
	if(strcmp(varName,"state")==0)
		return state;
	return -1;
}
void Coin::SetVar(char* varName,int val)
{
	if(strcmp(varName,"state")==0)
		ChangeState(val);
	else if(strcmp(varName,"numCoin")==0)
		numCoin=val;
}
void Coin::ResetWhenReload(GSprite* _sprite)
{
	isCheckedContainer=false;
	sprite=_sprite;
	ani=new GAnimation(4,5,0.2,sprite);
}
void Coin::Save(fstream *fs)
{
	fs->write(reinterpret_cast<char*>(&ID),sizeof(ID));	//int ID, để khi load biết được đang load Obj nào
	int sizeObj=sizeof(*this);
	fs->write(reinterpret_cast<char*>(&sizeObj),sizeof(int));			//int sizeof(obj)
	fs->write(reinterpret_cast<char*>(this),sizeObj);
}
void Coin::Load(fstream *fs)
{
	int sizeObj;
	fs->read(reinterpret_cast<char*>(&sizeObj),sizeof(int));			//int sizeof(obj)
	fs->read(reinterpret_cast<char*>(this),sizeObj);
}
void Coin::ResetRect()
{
	rect.left=x;
	rect.top=y+1;
	rect.right=rect.left+width;
	rect.bottom=rect.top+height-1;
}