#pragma once
#include "math.h"
#include <list>
using namespace std;

#include "GCamera.h"
class GQuadTree;
class Cloud;
class GSprite;
class GObject;
class GGraphic;
class Game;

void ReadMap(char* fileName,bool isBright,Game* game);
int* ReadIntFromFile(char* fileName);
void trace(const char* sLog,char* filePath="D:\\TraceLog.log");
void GetListItems(list<GObject*>* lItems,list<GObject*>* staObjs,list<GObject*>* dynObjs);
void DrawNumber(GSprite* sprite,int number,int x,int y,char zoomX,char zoomY);
void DrawNumber(GSprite* sprite,int number,int x,int y);
void SaveGame(char* fileName,Game* game);
void LoadGame(char* fileName,Game* game);

/*char sTrace[10];
itoa(needTraceVar,sTrace,10);
trace(sTrace);*/
