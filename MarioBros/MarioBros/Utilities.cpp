#include "Utilities.h"
#include "Cloud.h"
#include "Hill.h"
#include "GQuadTree.h"
#include "Info.h"
#include "Clumn.h"
#include "Castle.h"
#include "Pipe.h"
#include "Brick.h"
#include "Ground.h"
#include "Stone.h"
#include "QBrick.h"
#include "Mario.h"
#include "Goomba.h"
#include "Koopa.h"
#include "PowerUp.h"
#include "Star.h"
#include "Pirhana.h"
#include "LifeFungus.h"
#include "Coin.h"
#include "Flag.h"
#include "CheckPoint.h"
#include "Sign.h"

#include <iostream>
#include <fstream>
using namespace std;


void ReadMap(char* fileName,bool isBright,Game* game)
{
	int *data=ReadIntFromFile(fileName);
	int sizeQuad,numObj,x,y,ID;
	bool isStatic=true;
	GObject* obj=NULL;
	if(game->quadTree!=NULL) delete game->quadTree;
	sizeQuad=max(data[0],data[1])*TILE_SIZE;
	game->quadTree=new GQuadTree(0,0,sizeQuad,0);
	numObj=data[2]+data[3]+data[4]+data[5];				//Số đối tượng
	for(int i=0;i<numObj;i++)
	{
		x=data[6+i*3]*TILE_SIZE;									//Mỗi phần tử lưu bởi 3 con số
		y=data[7+i*3]*TILE_SIZE;
		ID=data[8+i*3];
		switch(ID)
		{
		case 10:
			obj=new Cloud(x,y,80,80,ID,game->sprites[S_SCENE]);
			isStatic=true;
			break;
		case 11:
			obj=new Cloud(x,y,120,80,ID,game->sprites[S_SCENE]);
			isStatic=true;
			break;
		case 12:
			obj=new Cloud(x,y,160,80,ID,game->sprites[S_SCENE]);
			isStatic=true;
			break;
		case 13:
			obj=new Clumn(x,y,80,40,ID,game->sprites[S_SCENE]);
			isStatic=true;
			break;
		case 14:
			obj=new Clumn(x,y,120,40,ID,game->sprites[S_SCENE]);
			isStatic=true;
			break;
		case 15:
			obj=new Clumn(x,y,160,40,ID,game->sprites[S_SCENE]);
			isStatic=true;
			break;
		case 16:
			obj=new Hill(x,y,120,80,ID,game->sprites[S_SCENE]);
			isStatic=true;
			break;
		case 17:
			obj=new Hill(x,y,200,120,ID,game->sprites[S_SCENE]);
			isStatic=true;
			break;
		case 18:
			obj=new Castle(x,y,200,200,ID,game->sprites[S_CASTLE]);
			isStatic=true;
			break;
		case 20:
			obj=new Pipe(x,y,80,80,ID,game->sprites[S_PIPE]);				//Ống thấp
			isStatic=true;
			break;
		case 21:
			obj=new Pipe(x,y,80,120,ID,game->sprites[S_PIPE]);			//Ống trung bình
			isStatic=true;
			break;
		case 22:
			obj=new Pipe(x,y,80,160,ID,game->sprites[S_PIPE]);			//Ống cao
			isStatic=true;
			break;
		case 23:
			obj=new Pipe(x,y,80,80,ID,game->sprites[S_PIPE]);				//Ống ngang
			isStatic=true;
			break;
		case 24: case 51:
			obj=new Brick(x,y,40,40,isBright,ID,game->sprites[S_BASIC]);
			isStatic=true;
			break;
		case 25:
			obj=new QBrick(x,y,40,40,isBright,ID,game->sprites[S_BASIC]);
			isStatic=true;
			break;
		case 26:
			obj=new Ground(x,y,40,40,isBright,ID,game->sprites[S_BASIC]);
			isStatic=true;
			break;
		case 27:
			obj=new Stone(x,y,40,40,isBright,ID,game->sprites[S_BASIC]);
			isStatic=true;
			break;
		case 28:
			obj=new Pipe(x,y,80,80,ID,game->sprites[S_PIPE]);				//Ống nối
			isStatic=true;
			break;
		case 29:
			obj=new Flag(x,y,32,440,ID,game->sprites[S_FLAG]);
			isStatic=true;
			break;
		case 30:
			obj=new PowerUp(x,y-1,40,40,ID,game->sprites[S_ITEM]);
			isStatic=false;
			break;
		case 31:
			obj=new LifeFungus(x,y-1,40,40,ID,game->sprites[S_ITEM]);
			isStatic=false;
			break;
		case 32:
			obj=new Star(x,y-1,40,40,ID,game->sprites[S_ITEM]);
			isStatic=false;
			break;
		case 33:
			obj=new Pirhana(x,y-1,40,80,ID,game->sprites[S_PIRHANA]);
			isStatic=false;
			break;
		case 34:
			obj=new Coin(x,y-1,40,40,ID,game->sprites[S_ITEM]);
			isStatic=true;
			break;
		case 40:
			obj=new Mario(x,y-1,40,40,ID,game->sprites[S_SMARIO],game->sprites[S_BMARIO],game->sprites[S_BULLET],game->sprites[S_EXPLOSION],game);
			if(game->state==GS_REPLAY&&game->checkPoint->stage==game->stage)		//Đặt Mario vào CheckPoint...
			{																//...nếu đang Replay và có CheckPoint...
				obj->x=game->checkPoint->x;									//...trùng stage với game.
				obj->y=game->checkPoint->y-1;
				obj->ResetRect();
			}
			if(game->state==GS_NEXT_STAGE||game->state==GS_RETURN_STAGE||game->state==GS_SUB_STAGE)
			{
				obj->SetVar("isShotable",game->cloneMario->isShotable);
				obj->SetVar("isBig",game->cloneMario->isBig);
			}
			game->camera->obj=obj;
			isStatic=false;
			break;
		case 41:
			obj=new Goomba(x,y-1,40,40,isBright,ID,game->sprites[S_GOOMBA],game);
			isStatic=false;
			break;
		case 42:
			obj=new Koopa(x,y-1,40,40,isBright,ID,game->sprites[S_KOOPA],game);
			isStatic=false;
			break;
		case 50:
			obj=new CheckPoint(x,y,game->stage);
			isStatic=true;
			break;
		case 52:case 53:
			obj=new Sign(x,y,80,40,ID);
			isStatic=true;
			break;
		}
		obj->game=game;
		if(obj!=NULL)
			game->quadTree->Add(obj,isStatic);
		obj=NULL;
	}
}
int* ReadIntFromFile(char* fileName)
{
	fstream fs;
	int buffer,size,*result;
	fs.open(fileName,ios::in|ios::binary|ios::ate);
	size=fs.tellg()/sizeof(int);
	result=new int[size];
	fs.seekp(ios::beg);

	for(int i=0;i<size;i++)
	{
		fs.read(reinterpret_cast<char*>(&buffer), sizeof(buffer));
		result[i]=buffer;
	}
	return result;
}

void trace(const char* sLog,char* filePath)
{
	fstream fileLog;
	fileLog.open(filePath,ios::app);
	fileLog<<sLog<<"\n";
}
void GetListItems(list<GObject*>* lItems,list<GObject*>* staObjs,list<GObject*>* dynObjs)
{
	list<GObject*>::iterator i;
	GObject* obj;
	for(i=staObjs->begin();i!=staObjs->end();i++)
	{
		obj=*i;
		if(obj->ID>=30&&obj->ID<40)
			lItems->push_back(obj);
	}
	for(i=dynObjs->begin();i!=dynObjs->end();i++)
	{
		obj=*i;
		if(obj->ID>=30&&obj->ID<40)
			lItems->push_back(obj);
	}
}
void DrawNumber(GSprite* sprite,int number,int x,int y,char zoomX,char zoomY)
{
	char temp;
	RECT rSrc;
	int numWidth=sprite->width/10;
	do
	{
		temp=number%10;
		number=number/10;
		rSrc.left=numWidth*temp;
		rSrc.right=numWidth*(temp+1);
		rSrc.top=0;
		rSrc.bottom=sprite->height;
		sprite->Draw(x,y,zoomX,zoomY,rSrc,0.1);
		x-=numWidth;
	}while(number>0);
}
void DrawNumber(GSprite* sprite,int number,int x,int y)
{
	DrawNumber(sprite,number,x,y,1,1);
}

void SaveGame(char* fileName,Game* game)
{
	fstream fs;
	GObject* obj;
	list<GObject*>::iterator i;
	list<GObject*> lStatic,lDynamic;

	fs.open(fileName,ios::out|ios::binary);
	game->quadTree->GetObjectsAllNode(&lStatic,&lDynamic);
	fs.write(reinterpret_cast<char*> (&game->stage),sizeof(char));	//char stage
	fs.write(reinterpret_cast<char*> (&game->quadTree->rect.bottom),sizeof(LONG));	//LONG size quadTree
	for(i=lStatic.begin();i!=lStatic.end();i++)
		(*i)->Save(&fs);
	for(i=lDynamic.begin();i!=lDynamic.end();i++)
		(*i)->Save(&fs);
	int endFile=-1;
	fs.write(reinterpret_cast<char*>(&endFile),sizeof(int));
	fs.close();
}
void LoadGame(char* fileName,Game* game)
{
	fstream		fs;
	LONG		sizeQuadTree;
	int			ID,sizeObj;
	GObject*		obj;
	bool		isStatic;
	Mario*		mario;

	fs.open(fileName,ios::in|ios::binary);
	fs.read(reinterpret_cast<char*> (&game->stage),sizeof(char));				//char stage
	fs.read(reinterpret_cast<char*> (&sizeQuadTree),sizeof(LONG));				//LONG size quadTree
	game->quadTree=new GQuadTree(0,0,sizeQuadTree,0);
	do 
	{
		obj=NULL;
		fs.read(reinterpret_cast<char*>(&ID),sizeof(int));				//int ID
		switch(ID)
		{
		case 10: case 11: case 12:	
			obj=new Cloud();
			obj->Load(&fs);
			obj->ResetWhenReload(game->sprites[S_SCENE]);
			isStatic=true;
			break;
		case 13: case 14: case 15:
			obj=new Clumn();
			obj->Load(&fs);
			obj->ResetWhenReload(game->sprites[S_SCENE]);
			isStatic=true;
			break;
		case 16: case 17:
			obj=new Hill();
			obj->Load(&fs);
			obj->ResetWhenReload(game->sprites[S_SCENE]);
			isStatic=true;
			break;
		case 18:
			obj=new Castle();
			obj->Load(&fs);
			obj->ResetWhenReload(game->sprites[S_CASTLE]);
			isStatic=true;
			break;
		case 20: case 21: case 22: case 23: case 28:
			obj=new Pipe();				//Ống thấp
			obj->Load(&fs);
			obj->ResetWhenReload(game->sprites[S_PIPE]);
			isStatic=true;
			break;
		case 24: case 51:
			obj=new Brick();
			obj->Load(&fs);
			obj->ResetWhenReload(game->sprites[S_BASIC]);
			isStatic=true;
			break;
		case 25:
			obj=new QBrick();
			obj->Load(&fs);
			obj->ResetWhenReload(game->sprites[S_BASIC]);
			isStatic=true;
			break;
		case 26:
			obj=new Ground();
			obj->Load(&fs);
			obj->ResetWhenReload(game->sprites[S_BASIC]);
			isStatic=true;
			break;
		case 27:
			obj=new Stone();
			obj->Load(&fs);
			obj->ResetWhenReload(game->sprites[S_BASIC]);
			isStatic=true;
			break;
		case 29:
			obj=new Flag();
			obj->Load(&fs);
			obj->ResetWhenReload(game->sprites[S_FLAG]);
			isStatic=true;
			break;
		case 30:
			obj=new PowerUp();
			obj->Load(&fs);
			obj->ResetWhenReload(game->sprites[S_ITEM]);
			isStatic=false;
			break;
		case 31:
			obj=new LifeFungus();
			obj->Load(&fs);
			obj->ResetWhenReload(game->sprites[S_ITEM]);
			isStatic=false;
			break;
		case 32:
			obj=new Star();
			obj->Load(&fs);
			obj->ResetWhenReload(game->sprites[S_ITEM]);
			isStatic=false;
			break;
		case 33:
			obj=new Pirhana();
			obj->Load(&fs);
			obj->ResetWhenReload(game->sprites[S_PIRHANA]);
			isStatic=true;
			break;
		case 34:
			obj=new Coin();
			obj->Load(&fs);
			obj->ResetWhenReload(game->sprites[S_ITEM]);
			isStatic=true;
			break;
		case 40:
			obj=new Mario();
			obj->Load(&fs);
			mario=(Mario*)obj;
			mario->sBig=game->sprites[S_BMARIO];
			obj->ResetWhenReload(game->sprites[S_SMARIO]);
			mario->game=game;
			mario->camera=game->camera;
			game->camera->obj=obj;
			isStatic=false;
			break;
		case 41:
			obj=new Goomba();
			obj->Load(&fs);
			obj->ResetWhenReload(game->sprites[S_GOOMBA]);
			isStatic=false;
			break;
		case 42:
			obj=new Koopa();
			obj->Load(&fs);
			obj->ResetWhenReload(game->sprites[S_KOOPA]);
			isStatic=false;
			break;
		case 50:
			obj=new CheckPoint();
			obj->Load(&fs);
			isStatic=true;
			break;
		case 52:case 53:
			obj=new Sign();
			obj->Load(&fs);
			isStatic=true;
			break;
		}
		
		if(obj!=NULL)
		{
			obj->game=game;
			game->quadTree->Add(obj,isStatic);
		}
	} while (ID!=-1);			//Lặp cho đến khi có ký hiệu kết thúc file.
	fs.close();
}