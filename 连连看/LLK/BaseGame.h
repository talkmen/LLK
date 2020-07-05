#pragma once
#include "GameControl.h"
class CBaseGame :
	public CGameControl
{
public:
	CBaseGame();
	~CBaseGame();
	Vertex startGame();
};

