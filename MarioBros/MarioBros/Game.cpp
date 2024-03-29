//Framework ----------------------
#include "d3d9.h"
#include "d3dx9.h"
#include <tchar.h>
#include "time.h"
#include "Game.h"
#include "GGraphic.h"
#include "GInput.h"
#include "GSprite.h"
#include "GAnimation.h"
#include "GTimeManager.h"
#include "stdio.h"
//--------------------------------

#include "GQuadTree.h"
#include "Info.h"
#include "Utilities.h"
#include "GObject.h"
#include "Mario.h"
#include "CheckPoint.h"
#include "Score.h"

#include <list>
using namespace std;
Game::Game(HWND _hWnd, HINSTANCE _hInstance)
{
	//Framework ----------------------
	hWnd=_hWnd;
	hInstance=_hInstance;
	input=new GInput(hWnd,hInstance,SCREEN_WIDTH,SCREEN_HEIGHT);
	g=new GGraphic(hWnd);
	a=new GAudio(hWnd); 
	timeManager=new GTimeManager();
	D3DXCreateFont(g->device,30,0,FW_BOLD,0,false,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,TEXT("Arial"),&fontArial);
	srand((unsigned)(time(NULL)));
	//--------------------------------
	
	for(int i=0;i<10;i++) sprites[i]=NULL;
	sprites[S_CASTLE]	=new GSprite(g,"Image\\Castle.bmp");
	sprites[S_SCENE]	=new GSprite(g,"Image\\Scene.bmp");
	sprites[S_PIPE]		=new GSprite(g,"Image\\Pipe.bmp");
	sprites[S_BASIC]	=new GSprite(g,"Image\\Basic.png");
	sprites[S_SMARIO]	=new GSprite(g,"Image\\SmallMario.png");
	sprites[S_BMARIO]	=new GSprite(g,"Image\\BigMario.png");
	sprites[S_GOOMBA]	=new GSprite(g,"Image\\Goomba.bmp");
	sprites[S_KOOPA]	=new GSprite(g,"Image\\Koopa.bmp");
	sprites[S_ITEM]		=new GSprite(g,"Image\\Item.png");
	sprites[S_INFO]		=new GSprite(g,"Image\\Info.png");
	sprites[S_NUMBER]	=new GSprite(g,"Image\\Number.bmp");
	sprites[S_PIRHANA]	=new GSprite(g,"Image\\Pirhana.png");
	sprites[S_FLAG]		=new GSprite(g,"Image\\Flag.png");
	sprites[S_BULLET]	=new GSprite(g,"Image\\FireBullet.PNG");
	sprites[S_EXPLOSION]=new GSprite(g,"Image\\Explosion.PNG");

	camera=new GCamera(0,0,800,600);
	
	quadTree	=NULL;
	cloneMario	=new Mario();
	checkPoint	=new CheckPoint();
	isBright	=true;
	score=coin	=0;
	numLife		=3;
	state		=GS_MENU;
	//state       =GS_WIN;
	stage		=1;
	isUseCheckPoint	=false;
	timeGame=300;					
	wait1Sec=0;
	//waitbullet=0;

	sBackground=a->LoadSound("Sounds\\Background.wav"); 
	sGameOver=a->LoadSound("Sounds\\GameOver.wav"); 
	sWinState=a->LoadSound("Sounds\\WinStage.wav"); 
	sFireBall=a->LoadSound("Sounds\\fireball.wav"); 
	
	sJump=a->LoadSound("Sounds\\Jump.wav"); 
	sCoin1=a->LoadSound("Sounds\\Coin.wav"); 
	sPowerUp=a->LoadSound("Sounds\\PowerUp.wav"); 
	sDeath=a->LoadSound("Sounds\\Death.wav"); 
	sMip=a->LoadSound("Sounds\\mip.wav"); 
	sBonusRise=a->LoadSound("Sounds\\BonusRise.wav"); 
	sBrickBreaked=a->LoadSound("Sounds\\BrickBreaked.wav"); 
	sKick=a->LoadSound("Sounds\\kick.wav"); 
	sCoin2=a->LoadSound("Sounds\\Coin.wav"); 
	sCoin3=a->LoadSound("Sounds\\Coin.wav"); 
	sCoin4=a->LoadSound("Sounds\\Coin.wav"); 
	sPipeWarp=a->LoadSound("Sounds\\PipeWarp.wav");
	sBump=a->LoadSound("Sounds\\bump.wav");
	sLife=a->LoadSound("Sounds\\Life.wav");

	//_mario		=new Mario();
	//------K
	menu	    = g->CreateSurface("Image\\menu1.jpg");
	//itemMenu= g->CreateSurface("Image\\ItemMenu.png");
	about       = g->CreateSurface("Image\\About.jpg");
	gameOver    = g->CreateSurface("Image\\GameOver.jpg");
	gameWin     = g->CreateSurface("Image\\GameWin.jpg");
	gameConfirm = g->CreateSurface("Image\\GameConfirm.jpg");
	mariomenu   = new GSprite(g,"Image\\fungus.png");
	sprAuthor   = new GSprite(g,"Image\\author.png");
	sprControls = new GSprite(g, "Image\\controls.png");
	posymenu    = 190;
	posxmenu    = 238;
	selectedIndex = 0;
	posxArr = new int[4];
	posxArr[0] = posxmenu;
	posxArr[1] = 225;
	posxArr[2] = 280;
	posxArr[3] = 300;
	posymenuC   = 150; 
	//-------
}
void Game::GameRun()
{
	timeManager->LimitFPS(60);
	TPF=timeManager->TPF;
	input->GetMouse();	
	input->GetKey();
	Update();
	Render();
}
void Game::ProcessInput()
{
	switch(state)
	{
	case GS_MENU:
	
	    //When player enter hot key.
		if(input->KeyDown(DIK_N))
		{
			//Test.mm	World1-1.mm
			ChangeStage(1);
			ChangeState(GS_PLAYING);
		}
		else if(input->KeyDown(DIK_L))
			ChangeState(GS_LOAD);
		else if(input->KeyDown(DIK_Q))
			PostQuitMessage(0);
		else if (input->KeyDown(DIK_A))
		    ChangeState(GS_ABOUT);

		//-----K
		else if(input->KeyPress(DIK_DOWN))
		{
			posymenu+=40;
			selectedIndex++;
			if(posymenu>310){
				posymenu=190;
				selectedIndex = 0;
			}
			posxmenu=posxArr[selectedIndex];
			a->PlaySound(sFireBall);
		}
		else if(input->KeyPress(DIK_UP))
		{
			posymenu-=40;
			selectedIndex--;
			if(posymenu<190){
				posymenu=310;
				selectedIndex = 3;
			}
			posxmenu = posxArr[selectedIndex];
			a->PlaySound(sFireBall);
		}
		else if(input->KeyPress(DIK_RETURN))
		{
			a->PlaySound(sJump);
			if(posymenu==190)						//New game
			{
				//Test.mm	World1-1.mm
				ChangeStage(1);
				ChangeState(GS_PLAYING);
				score=0;							
				numLife=3;
			}
			else if(posymenu==230)
			{
				ChangeState(GS_LOAD);
			}
			/*else if(posymenu==400)
			{
				ChangeState(GS_SAVE);
			}*/
			else if(posymenu==270)
			{
				ChangeState(GS_ABOUT);
			}
			else if(posymenu==310)
			{
				PostQuitMessage(0);
			}
		}
		//------

		break;
	case GS_PLAYING:
		//waitbullet+=TPF;
		if(input->KeyDown(DIK_ESCAPE))
		{
			//ChangeState(GS_SAVE);
            SaveGame("Save\\Save.sm",this);
            if(quadTree!=NULL) delete quadTree;
            quadTree=NULL;
			ChangeState(GS_CONFIRM);
			a->StopSound(sBackground);
		}
		break;
	case GS_WIN: case GS_GAMEOVER:
		if(input->KeyDown(DIK_RETURN)||input->KeyDown(DIK_ESCAPE))
			ChangeState(GS_MENU);
		break;
	case GS_ABOUT:
		if(input->KeyDown(DIK_ESCAPE))
			ChangeState(GS_MENU);
		break;
	case GS_CONFIRM:
	    if (input->KeyPress(DIK_RIGHT) || input->KeyPress(DIK_LEFT))
	    {
	        //posymenuC += 230;
	        if (posymenuC == 150)
	        {
	            posymenuC = 380;
	        }else if (posymenuC == 380)
	        {
	            posymenuC = 150;
	        }
	        a->PlaySound(sFireBall);
	    }/*
	    else if (input->KeyPress(DIK_LEFT))
	    {
            posymenuC -=230;
            if (posymenuC < 150)
            {
                posymenuC = 150;
            }
            a->PlaySound(sFireBall);
	    }*/
	    else if(input->KeyPress(DIK_RETURN))
	    {
            if (posymenuC == 150)
            {
                ChangeState(GS_MENU);
                a->StopSound(sBackground);
            } 
            else if (posymenuC == 380)
            {
                ChangeState(GS_LOAD);
            }
            	    
	    }
	    break;
	}
}
void Game::Update()
{
	GObject* obj;
	Score* sco;
	list<GObject*>::iterator i;
	list<Score*>::iterator iScore;
	ProcessInput();
	switch(state)
	{
	case GS_PLAYING:
		if(numLife==0)
			ChangeState(GS_GAMEOVER);
		wait1Sec+=TPF;
		if(wait1Sec>1)
		{
			wait1Sec-=1;
			timeGame--;
		}

		//Xóa những object cần xóa
		for(i=staticObjs.begin();i!=staticObjs.end();i++)
		{
			obj=*i;
			if(obj->GetVar("isNeedDelete")==1)
				quadTree->DeleteObj(obj,true);
		}
		for(i=dynamicObjs.begin();i!=dynamicObjs.end();i++)
		{
			obj=*i;
			if(obj->GetVar("isNeedDelete")==1)
				quadTree->DeleteObj(obj,false);
		}
		
		//Làm rỗng danh sách
		staticObjs.clear();
		dynamicObjs.clear();

		quadTree->GetObjectsFromCamera(camera->rect,&staticObjs,&dynamicObjs);

		//Cập nhật. Chỉ cập nhật những đối tượng ở trước Camera một khoảng  và sau camera một khoảng 
		camera->Update(TPF,quadTree);
		for(i=staticObjs.begin();i!=staticObjs.end();i++)
		{
			obj=*i;
			if(obj->x>camera->x-10&&obj->x<camera->x+WIDTH+10)
				obj->Update(&staticObjs,&dynamicObjs,input,TPF);
		}
		for(i=dynamicObjs.begin();i!=dynamicObjs.end();i++)
		{
			obj=*i;
			if(obj->x>camera->x-WIDTH&&obj->x<camera->x+WIDTH+100)
				obj->Update(&staticObjs,&dynamicObjs,input,TPF);
			//if(obj->ID==40)
			//{
			//	Mario* mario=(Mario*)(*i);
			//	_mario=mario;
			//}
		}
		lScoreRemove.clear();
		for(iScore=lScore.begin();iScore!=lScore.end();iScore++)
		{
			sco=*iScore;
			sco->Update(TPF);
			if(sco->isNeedDelete==true)
			{
				delete sco;
				lScoreRemove.push_back(sco);
			}
		}
		for(iScore=lScoreRemove.begin();iScore!=lScoreRemove.end();iScore++)
		{
			lScore.remove((*iScore));
		}
		quadTree->Update(dynamicObjs);
		break;
	case GS_NEXT_STAGE:				//Khi đổi màn
		ChangeStage(stage+1);
		break;
	case GS_SUB_STAGE:				//Chui hầm (màn phụ).
		ChangeSubStage(stage);
		a->PlaySound(sPipeWarp);
		break;
	case GS_REPLAY: 				//Chết, chơi lại
		ChangeStage(stage);
		break;
	case GS_RETURN_STAGE:
		GObject* oTemp;
		ChangeStage(stage);
		quadTree->GetObjectsAllNode(&staticObjs,&dynamicObjs);
		for(i=staticObjs.begin();i!=staticObjs.end();i++)
		{
			obj=*i;
			if(obj->ID==53)					//Vị trí lên.
			{
				oTemp=obj;
				
			}
		}
		for(i=dynamicObjs.begin();i!=dynamicObjs.end();i++)
		{
			obj=*i;
			if(obj->ID==40)
			{				
				obj->x=oTemp->x;
				obj->y=oTemp->y-TILE_SIZE*2;
				obj->ResetRect();	
			}
		}
		quadTree->Update(dynamicObjs);		
	}
}
void Game::Render()
{
	//Framework ----------------------
	g->device->BeginScene();
	g->spriteDX->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_DEPTH_FRONTTOBACK);
	g->device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT); 
	g->device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
	g->device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
	g->device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	//--------------------------------

	//Vẽ nằm hết ở đây
	GObject* obj;
	list<GObject*>::iterator i;
	list<Score*>::iterator iScore;
	switch(state)
	{
	case GS_MENU:
		g->device->Clear(0,NULL,D3DCLEAR_TARGET,D3DCOLOR_XRGB(0,0,0),1.0,0);
		Menu();
		break;
	case GS_PLAYING:
		if(isBright==true)
			g->device->Clear(0,NULL,D3DCLEAR_TARGET,D3DCOLOR_XRGB(59,185,255),1.0,0);
		else g->device->Clear(0,NULL,D3DCLEAR_TARGET,D3DCOLOR_XRGB(0,0,0),1.0,0);

		RECT rInfo;
		rInfo.left=0;rInfo.right=132; rInfo.top=0; rInfo.bottom=16;
		sprites[S_INFO]->Draw(50,20,1,1,rInfo,0.1);
		rInfo.top=16; rInfo.bottom=34;
		sprites[S_INFO]->Draw(500,20,1,1,rInfo,0.1);
		DrawNumber(sprites[S_NUMBER],numLife,150,20);
		DrawNumber(sprites[S_NUMBER],score,150,40);
		DrawNumber(sprites[S_NUMBER],coin,550,20);
		DrawNumber(sprites[S_NUMBER],timeGame,700,40);

		for(i=staticObjs.begin();i!=staticObjs.end();i++)
		{
			obj=*i;
			if(obj->x>camera->x-800&&obj->x<camera->x+WIDTH+10)
				obj->Render(camera);
		}
		for(i=dynamicObjs.begin();i!=dynamicObjs.end();i++)
		{
			obj=*i;
			if(obj->x>camera->x-800&&obj->x<camera->x+WIDTH+10)
				obj->Render(camera);
		}
		for(iScore=lScore.begin();iScore!=lScore.end();iScore++)
			(*iScore)->Render(camera);
		break;
	case GS_WIN:
		g->device->Clear(0,NULL,D3DCLEAR_TARGET,D3DCOLOR_XRGB(0,0,0),1.0,0);
		/*g->DrawTextAdvanced(L"You Won !",100,300,800,200,D3DXCOLOR(1,0,0,1),fontArial);
		g->DrawTextAdvanced(L"Press Enter or ESC to return Menu !",100,400,800,200,D3DXCOLOR(1,0,0,1),fontArial);*/
		g->device->StretchRect(gameWin, NULL, g->backBuffer, NULL, D3DTEXF_NONE);
		break;
	case GS_GAMEOVER:
		a->PlaySound(sGameOver); 
		a->StopSound(sBackground);
		g->device->Clear(0,NULL,D3DCLEAR_TARGET,D3DCOLOR_XRGB(0,0,0),1.0,0);
		g->device->StretchRect(gameOver, NULL, g->backBuffer, NULL, D3DTEXF_NONE);
		break;
	case GS_ABOUT:
		AboutGame();
		break;
	case GS_CONFIRM:
	    g->device->Clear(0,NULL,D3DCLEAR_TARGET,D3DCOLOR_XRGB(0,0,0),1.0,0);
	    GameConfirm();
	    break;
	    
	}
	
	//Framework ----------------------
	g->spriteDX->End();
	g->device->EndScene();
	g->device->Present(NULL,NULL,NULL,NULL);
	//--------------------------------
}

Game::~Game()
{
	if(quadTree!=NULL) delete quadTree;
	for(int i=0;i<10;i++)
		if(sprites[i]!=NULL) delete sprites[i];
	if(checkPoint) delete checkPoint;
	delete sJump;
	delete sCoin1;
	delete sCoin2;
	delete sCoin3;
	delete sCoin4;
	delete sPowerUp;
	delete sDeath;
	delete sMip;
	delete sBonusRise;
	delete sBrickBreaked;
	delete sKick;
	delete sPipeWarp;
	delete sBump;
	delete sLife;

	//Framework ----------------------
	delete g;
	delete input;
	delete timeManager;
	delete a; 
	//--------------------------------
}
void Game::ChangeState(char _state)
{
	state=_state;
	switch(state)
	{
	case GS_SAVE:
		SaveGame("Save\\Save.sm",this);
		if(quadTree!=NULL) delete quadTree;
		quadTree=NULL;
		ChangeState(GS_MENU);
		break;
	case GS_LOAD:
		LoadGame("Save\\Save.sm",this);
		SetIsBright(stage);
		ChangeState(GS_PLAYING);
		break;
	case GS_PLAYING:
		//a->PlaySound(sBackground); 
		camera->x=0;
		staticObjs.clear();
		dynamicObjs.clear();
		break;
	case GS_WIN:
		a->PlaySound(sWinState);
		break;
	}
}

void Game::ChangeStage(char _stage)
{
	if(isInSubStage==false)		//Nếu chuyển màn thì gán lại thời gian 
		timeGame=300;
	isInSubStage=false;
	stage=_stage;
	switch(stage)
	{
	case 1:
		ReadMap("Map\\World1-1.mm",true,this);
		//ReadMap("Map\\Test.mm",true,this);
		break;
	case 2:
		ReadMap("Map\\World1-2.mm",false,this);
		break;
	case 3:
		ReadMap("Map\\World1-3.mm",true,this);
		break;
	}
	SetIsBright(_stage);
	if(stage<4)
		ChangeState(GS_PLAYING);
	else ChangeState(GS_WIN);
		
}
void Game::ChangeSubStage(char _stage)
{
	isInSubStage=true;
	switch(_stage)
	{
	case 1:
		ReadMap("Map\\World1-1a.mm",false,this);
		isBright=false;
		break;
	case 2:
		ReadMap("Map\\World1-2a.mm",false,this);
		isBright=false;
		break;
	case 3:
		ReadMap("Map\\World1-3a.mm",false,this);
		isBright=false;
		break;
	}
	ChangeState(GS_PLAYING);
}
void Game::SetIsBright(char _stage)
{
	switch(stage)
	{
	case 1:
		isBright=true;
		break;
	case 2:
		isBright=false;
		break;
	case 3:
		isBright=true;
		break;
	}
}
void Game::AddScore(int _score,float _x,float _y)
{
	score+=_score;
	Score* sco=new Score(sprites[S_NUMBER],_x,_y,_score);
	lScore.push_back(sco);
}

//
void Game::Menu()
{	
	g->device->StretchRect(menu,NULL,g->backBuffer,NULL,D3DTEXF_NONE);
	menurect.top=0;
	menurect.left=0;
	menurect.right=96;
	menurect.bottom=98;
	mariomenu->Draw(posxmenu,posymenu,1.0,1.0,menurect,0.5);		
}
void Game::AboutGame()
{
	g->device->Clear(0,NULL,D3DCLEAR_TARGET,D3DCOLOR_XRGB(0,0,0),1.0,0);
	//g->device->StretchRect(about, NULL, g->backBuffer, NULL, D3DTEXF_NONE);
	sprControls->Draw(200, 100, 1.0, 1.0, 1.0);
	sprAuthor->Draw(200, 300, 1.0, 1.0, 1.0);
}
void Game::GameConfirm()
{
    g->device->StretchRect(gameConfirm,NULL,g->backBuffer,NULL,D3DTEXF_NONE);
    menurect.top=0;
    menurect.left=0;
    menurect.right=96;
    menurect.bottom=98;
    mariomenu->Draw(posymenuC,270,1.0,1.0,menurect,0.5);
}
//------