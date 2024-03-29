#include "PowerUp.h"
#include "GObject.h"
#include "Info.h"
#include "GAnimation.h"
#include "GSprite.h"
#include "GCollision.h"

PowerUp::PowerUp():GObject(){}
PowerUp::PowerUp(float _x, float _y,float width,float height,int _ID,GSprite* _sprite):GObject(_x,_y,width,height)
{
	sprite	=_sprite;
	ID	=_ID;
	ani=new GAnimation(4,5,0,sprite);

	xOld		=x;
	yOld		=y;
	ay=vx=vy	=0;
	state		=IS_IDLE;
	isFungus	=true;
	container	=NULL;
	isCheckedContainer	=false;
	isNeedDelete=false;
}
void PowerUp::Update(list<GObject*>* staObjs,list<GObject*>* dynObjs,GInput* input, float TPF)
{
	switch(state)
	{
	case IS_IDLE:
		CheckObjects(staObjs,dynObjs);
		break;
	case IS_ACTIVING:
		x+=vx*TPF;
		y+=vy*TPF+1/2*ay*TPF*TPF;
		if(y<container->y-TILE_SIZE-5)
			if(isFungus==true)
				ChangeState(IS_MOVING);
			else ChangeState(IS_READY);
		break;
	case IS_MOVING:
		Move(TPF,staObjs,dynObjs);
		break;
	}
	UpdateAnimation(TPF);
	ResetRect();
}
void PowerUp::CheckObjects(list<GObject*>* staObjs,list<GObject*>* dynObjs)
{
	
	list<GObject*>::iterator i;
	GObject* obj;
	if(isCheckedContainer==false)
		for(i=staObjs->begin();i!=staObjs->end();i++)
		{
			obj=*i;
			if(obj->ID==24||obj->ID==25)
				if(GCollision::RectVsRect(rect,obj->rect))
				{
					container=obj;
					break;
				}
		}
	for(i=dynObjs->begin();i!=dynObjs->end();i++)
	{
		obj=*i;
		if(obj->ID==40)		//Là Mario
			if(obj->GetVar("isBig")==1) 
				isFungus=false;
	}
	isCheckedContainer=true;
}
void PowerUp::Render(GCamera* camera)
{
	if(isFungus==true)
	{
		if(state!=IS_IDLE&&state!=IS_ATE)
			sprite->Draw(x-camera->x,y,ZOOM,ZOOM,ani->GetRect(1),0.75);
	}
	else
	{
		if(state!=IS_IDLE&&state!=IS_ATE)
			sprite->Draw(x-camera->x,y+8,ZOOM,ZOOM,ani->rect,0.75);
	}
}
void PowerUp::ChangeState(int _state)
{
	state=_state;
	switch(state)
	{
	case IS_ACTIVING:
		vy=-500;
		container->SetVar("isChanged",true);
		break;
	case IS_MOVING:
		vy=0;
		if(vx==100)
			vx=-100;
		else vx=100;
		break;
	case IS_READY:
		y=container->y-TILE_SIZE;
		break;
	case IS_ATE:
		isNeedDelete=true;
		break;
	}
}
void PowerUp::Move(float TPF,list<GObject*>* staObjs,list<GObject*>* dynObjs)
{
	GObject* obj;
	//Theo phương x
	x+=vx*TPF;
	ResetRect();
	list<GObject*>::iterator i;
	for(i=staObjs->begin();i!=staObjs->end();i++)
	{
		obj=*i;
		if(obj->ID>=20&&obj->ID<=29) //Nếu là thùng, đá , gạch...
			if(GCollision::RectVsRect(rect,obj->rect)==true)	
			{
				vx=-vx;
				x=xOld;
			}
	}
	//Theo phương y
	ay=G;
	vy+=ay*TPF;
	y+=vy*TPF+1.0/2*ay*TPF*TPF;
	ResetRect();
	for(i=staObjs->begin();i!=staObjs->end();i++)
	{
		obj=*i;
		if(obj->ID>=20&&obj->ID<=28) //Nếu là thùng, đá , gạch...
			if(GCollision::RectVsRect(rect,obj->rect)==true)	
			{
				ay=0;
				vy=0;
				y=yOld;
			}
	}

	xOld=x;
	yOld=y;
}
int PowerUp::GetVar(char* varName)
{
	if(strcmp(varName,"state")==0)
		return state;
	if(strcmp(varName,"isNeedDelete")==0)
		return isNeedDelete;
	if(strcmp(varName,"vx")==0)
		return vx;
	return -1;
}
void PowerUp::SetVar(char* varName,int val)
{
	if(strcmp(varName,"state")==0)
		ChangeState(val);
	else if(strcmp(varName,"vx")==0)
		vx=val;
}
void PowerUp::UpdateAnimation(float TPF)
{
	if(isFungus==false)
		ani->Update(4,7,TPF);
}
void PowerUp::ResetWhenReload(GSprite* _sprite)
{
	sprite=_sprite;
	ani=new GAnimation(4,5,0,sprite);
	isCheckedContainer=false;
}
void PowerUp::Save(fstream *fs)
{
	fs->write(reinterpret_cast<char*>(&ID),sizeof(ID));	//int ID, để khi load biết được đang load Obj nào
	int sizeObj=sizeof(*this);
	fs->write(reinterpret_cast<char*>(&sizeObj),sizeof(int));			//int sizeof(obj)
	fs->write(reinterpret_cast<char*>(this),sizeObj);
}
void PowerUp::Load(fstream *fs)
{
	int sizeObj;
	fs->read(reinterpret_cast<char*>(&sizeObj),sizeof(int));			//int sizeof(obj)
	fs->read(reinterpret_cast<char*>(this),sizeObj);
}