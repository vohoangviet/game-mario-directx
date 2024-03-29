#include "Brick.h"
#include "GObject.h"
#include "Info.h"
#include "GAnimation.h"
#include "GSprite.h"

Brick::Brick():GObject(){}
Brick::Brick(float _x, float _y,float width,float height,bool _isBright,int _ID,GSprite* _sprite):GObject(_x,_y,width,height)
{
	isBright	=_isBright;
	sprite		=_sprite;
	ID			=_ID;
	isChanged	=false;
	isNeedDelete=false;
	isContainCoin	=false;
	state		=TS_IDLE;
	yOld		=y;
	angle		=0;
	ani			=new GAnimation(4,4,0.5,sprite);
}
void Brick::Update(list<GObject*>* staObjs,list<GObject*>* dynObjs,GInput* input, float TPF)
{
	switch(state)
	{
	case TS_MOVEUP:
		vy+=ay*TPF;
		y+=vy*TPF+1/2*ay*TPF*TPF;
		if(y>yOld)
			ChangeState(TS_IDLE);
		break;
	case TS_BREAKING:
		xBreak1+=vxBreak1*TPF;
		xBreak2+=vxBreak2*TPF;
		vyBreak1+=ayBreak*TPF;
		vyBreak2+=ayBreak*TPF;
		yBreak1+=vyBreak1*TPF+0.5*ayBreak*TPF*TPF;
		yBreak2+=vyBreak2*TPF+0.5*ayBreak*TPF*TPF;
		if(yBreak1>y+600)
			ChangeState(TS_BREAKED);
		if(angle<2*PI)
			angle+=0.2;
		else angle=0;
		break;
	}
}
void Brick::Render(GCamera *camera)
{
	if(ID!=51)				//Nếu không phải là gạch ẩn.
	{
		if(state==TS_IDLE||state==TS_MOVEUP)				//Nếu chưa vỡ
		{
			if(isBright)
			{
				if(!isChanged)
					sprite->Draw(x-camera->x,y,ZOOM,ZOOM,ani->GetRect(0),0.5);
				else sprite->Draw(x-camera->x,y,ZOOM,ZOOM,ani->GetRect(3),0.5);
			}
			else
			{
				if(!isChanged)
					sprite->Draw(x-camera->x,y,ZOOM,ZOOM,ani->GetRect(4),0.5);
				else sprite->Draw(x-camera->x,y,ZOOM,ZOOM,ani->GetRect(7),0.5);
			}
		}
		else if(state==TS_BREAKING)								//Nếu vỡ và chưa bị biến đổi
		{
			if(isBright==true)
			{
				sprite->Draw(xBreak1-camera->x,yBreak1,ZOOM,ZOOM,D3DXVECTOR2(10,10),angle,D3DCOLOR_XRGB(255,255,255),ani->GetRect(12),0.2);
				sprite->Draw(xBreak2-camera->x,yBreak2,ZOOM,ZOOM,D3DXVECTOR2(10,10),angle,D3DCOLOR_XRGB(255,255,255),ani->GetRect(12),0.2);
				sprite->Draw(2*x-xBreak1-camera->x,yBreak1,-ZOOM,ZOOM,D3DXVECTOR2(-10,10),-angle,D3DCOLOR_XRGB(255,255,255),ani->GetRect(12),0.2);
				sprite->Draw(2*x-xBreak2-camera->x,yBreak2,-ZOOM,ZOOM,D3DXVECTOR2(-10,10),-angle,D3DCOLOR_XRGB(255,255,255),ani->GetRect(12),0.2);
			}
			else
			{
				sprite->Draw(xBreak1-camera->x,yBreak1,ZOOM,ZOOM,D3DXVECTOR2(10,10),angle,D3DCOLOR_XRGB(255,255,255),ani->GetRect(13),0.2);
				sprite->Draw(xBreak2-camera->x,yBreak2,ZOOM,ZOOM,D3DXVECTOR2(10,10),angle,D3DCOLOR_XRGB(255,255,255),ani->GetRect(13),0.2);
				sprite->Draw(2*x-xBreak1-camera->x,yBreak1,-ZOOM,ZOOM,D3DXVECTOR2(-10,10),-angle,D3DCOLOR_XRGB(255,255,255),ani->GetRect(13),0.2);
				sprite->Draw(2*x-xBreak2-camera->x,yBreak2,-ZOOM,ZOOM,D3DXVECTOR2(-10,10),-angle,D3DCOLOR_XRGB(255,255,255),ani->GetRect(13),0.2);
			}
		}
	}
	else if(isChanged==true)
	{
		if(isBright==true)
			sprite->Draw(x-camera->x,y,ZOOM,ZOOM,ani->GetRect(3),0.5);
		else sprite->Draw(x-camera->x,y,ZOOM,ZOOM,ani->GetRect(7),0.5);
	}
}
void Brick::SetVar(char* varName,int val)
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
	if(strcmp(varName,"isContainCoin")==0)
		isContainCoin=val;
}
int Brick::GetVar(char* varName)
{
	if(strcmp(varName,"isChanged")==0)
		return isChanged;
	if(strcmp(varName,"state")==0)
		return state;
	if(strcmp(varName,"isNeedDelete")==0)
		return isNeedDelete;
	if(strcmp(varName,"isContainCoin")==0)
		return isContainCoin;
	return -1;
}
void Brick::ChangeState(char _state)
{
	state=_state;
	switch(state)
	{
	case TS_IDLE:
		y=yOld;
		vy=0;
		ay=0;
	case TS_MOVEUP:
		vy=-200;
		ay=G;
		break;
	case TS_BREAKING:
		game->score+=50;
		xBreak1=xBreak2=x+TILE_SIZE/2;
		yBreak1=y;
		yBreak2=y+TILE_SIZE/2;
		vyBreak1=-900;
		vyBreak2=-600;
		vxBreak1=150;
		vxBreak2=100;
		ayBreak=G;
		break;
	case TS_BREAKED:
		isNeedDelete=true;
	}
}
void Brick::ResetWhenReload(GSprite* _sprite)
{
	sprite=_sprite;
	ani=new GAnimation(4,4,0.5,sprite);
}
void Brick::Save(fstream *fs)
{
	fs->write(reinterpret_cast<char*>(&ID),sizeof(ID));	//int ID, để khi load biết được đang load Obj nào
	int sizeObj=sizeof(*this);
	fs->write(reinterpret_cast<char*>(&sizeObj),sizeof(int));			//int sizeof(obj)
	fs->write(reinterpret_cast<char*>(this),sizeObj);
}
void Brick::Load(fstream *fs)
{
	int sizeObj;
	fs->read(reinterpret_cast<char*>(&sizeObj),sizeof(int));			//int sizeof(obj)
	fs->read(reinterpret_cast<char*>(this),sizeObj);
}