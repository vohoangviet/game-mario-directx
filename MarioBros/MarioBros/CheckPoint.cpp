#include "GObject.h"
#include "CheckPoint.h"

CheckPoint::CheckPoint():GObject()
{
	ID		=50;
	stage	=-1;
}
CheckPoint::CheckPoint(float _x,float _y, char _stage):GObject(_x,_y,0,0)
{
	stage	=_stage;
	ID		=50;
}
void CheckPoint::Save(fstream *fs)
{
	fs->write(reinterpret_cast<char*>(&ID),sizeof(ID));	//int ID, để khi load biết được đang load Obj nào
	int sizeObj=sizeof(*this);
	fs->write(reinterpret_cast<char*>(&sizeObj),sizeof(int));			//int sizeof(obj)
	fs->write(reinterpret_cast<char*>(this),sizeObj);
}
void CheckPoint::Load(fstream *fs)
{
	int sizeObj;
	fs->read(reinterpret_cast<char*>(&sizeObj),sizeof(int));			//int sizeof(obj)
	fs->read(reinterpret_cast<char*>(this),sizeObj);
}