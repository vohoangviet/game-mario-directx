#pragma once

class GObject;

class CheckPoint:public GObject
{
public:
	char	stage;

	CheckPoint();
	CheckPoint(float _x,float _y, char _stage);
	void Save(fstream *fs);
	void Load(fstream *fs);
};