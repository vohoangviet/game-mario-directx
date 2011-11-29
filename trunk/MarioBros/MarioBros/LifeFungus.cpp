#include "LifeFungus.h"
#include "Object.h"
#include "Info.h"
#include "Animation.h"
#include "Sprite.h"
#include "Collision.h"

LifeFungus::LifeFungus():Object(){}
LifeFungus::LifeFungus(float _x, float _y,float width,float height,int _ID,Sprite* _sprite):Object(_x,_y,width,height)
{
	sprite	=_sprite;
	ID	=_ID;	
	ani=new Animation(4,5,0,sprite);
	
	vx=vy=ay	=0;
	state		=IS_IDLE;
	xOld		=x;
	yOld		=y;
	container	=NULL;
	isCheckedContainer	=false;
	oldRect		=rect;
	isNeedDelete=false;	
	collisionList	=new list<Object*>;
}
LifeFungus::~LifeFungus()
{
	if(collisionList!=NULL)
		delete collisionList;
	collisionList=NULL;
}
void LifeFungus::Update(list<Object*>* staObjs,list<Object*>* dynObjs,Input* input, float TPF)
{
	if(state==IS_ATE) return;
	switch(state)
	{
	case IS_IDLE:
		CheckObjects(staObjs);
		break;
	case IS_ACTIVING:
		if(y<container->y-TILE_SIZE-1)
			ChangeState(IS_MOVING);
		x+=vx*TPF;
		y+=vy*TPF+1/2*ay*TPF*TPF;
		break;
	case IS_MOVING:
		Move(TPF,staObjs,dynObjs);
		break;
	}
	ResetRect();
}
void LifeFungus::CheckObjects(list<Object*>* staObjs)
{
	if(isCheckedContainer) return;

	list<Object*>::iterator i;
	Object* obj;
	for(i=staObjs->begin();i!=staObjs->end();i++)
	{
		obj=*i;
		if(obj->ID==24||obj->ID==25||obj->ID==51)
			if(Collision::RectVsRect(rect,obj->rect))
				container=obj;
	}
	isCheckedContainer=true;
}
void LifeFungus::ChangeState(char _state)
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
	case IS_ATE:
		isNeedDelete=true;
	}
}
void LifeFungus::Render(Camera* camera)
{
	if(state!=IS_IDLE&&state!=IS_ATE)
		sprite->Draw(x-camera->x,y,ZOOM,ZOOM,ani->GetRect(0),0.75);
}
void LifeFungus::Move(float TPF,list<Object*>* staObjs,list<Object*>* dynObjs)
{
	Object* obj;
	//Theo phương x
	x+=vx*TPF;
	ResetRect();
	list<Object*>::iterator i;
	for(i=staObjs->begin();i!=staObjs->end();i++)
	{
		obj=*i;
		if(obj->ID>=20&&obj->ID<=29) //Nếu là thùng, đá , gạch...
			if(Collision::RectVsRect(rect,obj->rect)==true)	
			{
				vx=-vx;
				x=xOld;
			}
	}
	//Theo phương y
	ay=G;
	vy+=ay*TPF;
	y+=vy*TPF+1.0/2*ay*TPF*TPF;
	oldRect=rect;
	ResetRect();
	collisionList->clear();
	for(i=staObjs->begin();i!=staObjs->end();i++)
	{
		obj=*i;
		if((obj->ID>=20&&obj->ID<=28)||obj->ID==51)				//Nếu là thùng, đá , gạch...
			if(Collision::RectVsRect(rect,obj->rect)==true)	
				collisionList->push_back(obj);
	}

	//Xét va chạm để không bị rơi
	if(collisionList->size()>0)
	{
		Object* obj;
		list<Object*>::iterator i;
		for(i=collisionList->begin();i!=collisionList->end();i++)
		{
			obj=*i;
			if(oldRect.bottom<obj->rect.bottom)
				if(obj->y-height<y)
				{
					y=obj->y-height;
					vy=0;
				}
		}
		ResetRect();
	}
	xOld=x;
	yOld=y;
}
int LifeFungus::GetVar(char* varName)
{
	if(strcmp(varName,"state")==0)
		return state;
	if(strcmp(varName,"isNeedDelete")==0)
		return isNeedDelete;
	if(strcmp(varName,"container")==0)
		return (int)container;
	if(strcmp(varName,"vx")==0)
		return vx;
	return -1;
}
void LifeFungus::SetVar(char* varName,int val)		//Dang lam nam doi huong
{
	if(strcmp(varName,"state")==0)
		ChangeState(val);
	else if(strcmp(varName,"vx")==0)
		vx=val;
	
}
void LifeFungus::ResetWhenReload(Sprite* _sprite)
{
	isCheckedContainer=false;
	collisionList	=new list<Object*>;
	sprite=_sprite;
	ani=new Animation(4,5,0,sprite);
}
void LifeFungus::Save(fstream *fs)
{
	fs->write(reinterpret_cast<char*>(&ID),sizeof(ID));	//int ID, để khi load biết được đang load Obj nào
	int sizeObj=sizeof(*this);
	fs->write(reinterpret_cast<char*>(&sizeObj),sizeof(int));			//int sizeof(obj)
	fs->write(reinterpret_cast<char*>(this),sizeObj);
}
void LifeFungus::Load(fstream *fs)
{
	int sizeObj;
	fs->read(reinterpret_cast<char*>(&sizeObj),sizeof(int));			//int sizeof(obj)
	fs->read(reinterpret_cast<char*>(this),sizeObj);
}