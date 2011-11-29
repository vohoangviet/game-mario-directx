#ifndef _DXAUDIO_H
#define _DXAUDIO_H

#include "dsutil.h"

//primary DirectSound object
extern CSoundManager *dsound;

//function prototypes
class Audio
{
public:
	Audio(HWND);
	CSound *LoadSound(char*);	
	void PlaySound(CSound *);
	void LoopSound(CSound *);
	void StopSound(CSound *);	
};

#endif

