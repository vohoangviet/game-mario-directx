#include "Score.h"
#include "GObject.h"
#include "Info.h"
#include "GAnimation.h"
#include "GSprite.h"
#include "Utilities.h"

Score::Score():GObject(){}
Score::Score(GSprite* _sprite,float _x,float _y,int _score):GObject(_x,_y,40,10)
{
	sprite			=_sprite;
	distanceMove	=0;
	vy				=-100;
	isNeedDelete	=false;
	score			=_score;
}
void Score::Update(float TPF)
{
	y+=vy*TPF;
	distanceMove+=vy*TPF;
	if(distanceMove<-100)
		isNeedDelete=true;
}
void Score::Render(GCamera* camera)
{
	DrawNumber(sprite,score,x-camera->x,y);
}
int Score::GetVar(char* varName)
{
	if(strcmp(varName,"isNeedDelete")==0)
		return isNeedDelete;
	return -1;
}