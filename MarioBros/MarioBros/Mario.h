#pragma once

#include "GAnimation.h"
#include "GSprite.h"
#include "GObject.h"
#include "Bullet.h"
#include "GAudio.h" 
#include <list>
using namespace std;

class GAnimation;
class GSprite;
class GObject;
class CheckPoint;

class Mario:public GObject
{
private:
	
	bool	isRender;
	float	waitNextRow;			//Thời gian tạo ra hiệu ứng nhấp nháy
	float	waitInFlag;				//Thời gian ở cột cờ;
	bool	isHasStar;
	bool	isChangeDirectionL;		//Đổi hướng 
	bool	isChangeDirectionR;
	float	waitLostStar;
	float	waitDieing;
	float	waitEatFlower;		//H
	float	waitShotting;
	bool	isProtected;
	bool	isShotting;
	float	waitProtect;			//Thời gian bảo vệ sau khi chết.
	float	waitProtectHidden;
	float	waitRender;				//Thời gian Render, tạo hiệu ứng nháy khi được boả vệ.
	float	waitInPipe;				//Thời gian trong ống.
	float	waitFrmZoom;			//Thời gian chuyển Frame.
	char	state;
	int		vMax;					//H
	char	frameZoom;				//Frame ở trạng thái MS_ZOOM_IN/OUT
public:
	
	float	yTemp;
	float	vx;
	float	vy;
	float	ax;
	float	ay;
	float	vyOld;
	float	waitChangeDir;		
	float	xOld;
	float	yOld;
	bool	isProtectedHidden;		//Được bảo vệ (không thể hiện ra hình ảnh)
	RECT	oldRECT;
	RECT	rHead;
	RECT	rAboveHead;
	char	renderRow;
	bool	isBig;
	
	bool	isFaceRight;
	bool	isJumming;
	bool	isShotable;
	bool	isCanGoDown;		//Có thể đi xuống hầm.
	float	timeJumped;
	float	waitsound;
	float	waitbullet;
	bool	isPlayingCoin;
	GSprite		*sBig;
	GSprite		*bullet1;//bullet
	GSprite		* bullet2;//explosion
	GAnimation	*aBig;
	CheckPoint	*checkPoint;
	//Audio		*a; 

	list<GObject*>	*collisionList;
	GCamera		*camera;

	Mario();
	Mario(float _x, float _y,float width,float height,int _ID,GSprite* _sSmall,GSprite* _sBig,GSprite* _bullet1,GSprite* _bullet2,Game* _game);
	~Mario();
	void Update(list<GObject*>* staObjs,list<GObject*>* dynObjs,GInput* input, float TPF);
	void Render(GCamera* camera);
	void ProcessInput(GInput *input);
	void Move(float TPF,list<GObject*>* staObjs,list<GObject*>* dynObjs);
	void CollisionEnemy();
	void UpdateAnimation(float TPF);
	void ResetRect();
	int GetVar(char* varName);
	void SetVar(char* varName,int val);
	void ResetWhenReload(GSprite* _sprite);
	void ChangeState(char _state);
	void Save(fstream *fs);
	void Load(fstream *fs);
	void CollisionOnTop(GObject* obj,list<GObject*>* staObjs,list<GObject*>* dynObjs);
	void EatCoin(float _x,float _y);		
	void EatLife(float _x,float _y);
};