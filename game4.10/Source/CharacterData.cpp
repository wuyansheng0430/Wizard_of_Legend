#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"
#include "CharacterData.h"

namespace game_framework {
	int CharacterData::Money = 0;
	int CharacterData::Diamond = 500;
	int CharacterData::HP = 500;
	int CharacterData::Max_HP = 500;
	int CharacterData::MP = 0;
	int CharacterData::Max_MP = 100;
	double CharacterData::Attack_Coefficient = 1;
	double CharacterData::Defense_Coefficient = 1;
	int CharacterData::Blood_Suck_Constant = 0;
	double CharacterData::Move_Coefficient = 1;
	double CharacterData::CD_Coefficient = 1;
	int CharacterData::MP_Charge_Constant = 4;
	

}