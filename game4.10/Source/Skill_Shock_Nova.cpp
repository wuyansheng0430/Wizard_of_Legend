#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <math.h>
#include "Skill_Shock_Nova.h"


namespace game_framework
{
	Skill_Shock_Nova::Skill_Shock_Nova(int mousreX, int mouseY, int *cxy) 		//中心往滑鼠位置的向量
	{
		Initialize(mousreX, mouseY, cxy);
		LoadBitmap();	
	}

	Skill_Shock_Nova::~Skill_Shock_Nova()
	{

	}

	void Skill_Shock_Nova::Initialize(int mouseX, int mouseY, int* cxy)
	{
		_damage = 1;
		_backDistance = 10;
		_hitbox[0] = 75;
		_hitbox[1] = 50;
		_hitbox[2] = 96;
		_hitbox[3] = 96;
		_lifeTimer = 300;
		_map_collision[0] = 0;			//圓心
		_map_collision[1] = 0;
		_map_collision[2] = 0;				//半徑
		_map_collision[3] = 0;
		_isDelete = false;
		_isStock = false;
		_speed = 20;
		_cast_distance = 30;
		_isInit = true;
		_counter = 5;
		_time = 6;
		_ani_skill[0].SetDelayCount(1);




	}

	void Skill_Shock_Nova::LoadBitmap()
	{
		_bm_skill_icon.LoadBitmap(SKILL_ICON_SHOCK_NOVA, RGB(50, 255, 0));


		int ani[3] = { SKILL_SHOCK_NOVA_01,SKILL_SHOCK_NOVA_02,SKILL_SHOCK_NOVA_03 };

		for (int i = 0; i < 3; i++)
			_ani_skill[0].AddBitmap(ani[i], RGB(50, 255, 0));

	}

	void Skill_Shock_Nova::OnMove(int *cxy, GameMap *map)
	{
		_counter == 0 ? NULL : _counter--;
		
		//_ani_skill[0].SetTopLeft(CHARACTER_SCREEN_X + _xy[0] - cxy[0], CHARACTER_SCREEN_X + _xy[1] - cxy[1]);
	

		if (_counter == 0)
		{
			_damage = 1;

			if (_lifeTimer == 0) //時間到
			{
				_isDelete = true;
			}

			_lifeTimer--;
			if (!_isInit)
			{
				_ani_skill[0].OnMove();
			}
			else
			{
				/*
				_xy[0] = cxy[0] - (_ani_skill[0].Width() - 70) / 2 + 2;
				_xy[1] = cxy[1] - (_ani_skill[0].Height() - 70) / 2 - 52;
				*/

				_xy[0] = cxy[0] - (_ani_skill[0].Width() - 70) / 2 + 2;
				_xy[1] = cxy[1] - (_ani_skill[0].Height() - 70) / 2 + 25;

				_isInit = false;
			}
		}

		_ani_skill[0].SetTopLeft(CHARACTER_SCREEN_X + _xy[0] - cxy[0], CHARACTER_SCREEN_Y + _xy[1] - cxy[1]);

		

	}

	int Skill_Shock_Nova::GetDamage(Enemy *enemy)
	{
		int *enemy_hitbox = enemy->GetHitbox();
		int *enemy_position = enemy->GetPosition();

		float x1 = _xy[0] + _hitbox[0];
		float y1 = _xy[1] + _hitbox[1];
		float r = _hitbox[2];

		float x2 = enemy_position[0] + enemy_hitbox[0];
		float y2 = enemy_position[1] + enemy_hitbox[1];
		float l2 = enemy_hitbox[2];
		float w2 = enemy_hitbox[3];

		if (pow(x1 - x2 + l2 / 2, 2) + pow(y1 - y2 + w2 / 2, 2) <= pow((l2 + w2) / 4 + r, 2) )
		{
			if (AttackedThisEnemy(enemy))
				return _damage;
		}

		return 0;
	}

	void Skill_Shock_Nova::OnShow()
	{
		if (!_isDelete && _counter==0)
		{
			_ani_skill[0].OnShow();
			if (_ani_skill[0].IsFinalBitmap())
			{
				_time == 0 ? _isDelete = true : _ani_skill[0].Reset(), _time--;
			}
		}
	}

	int* Skill_Shock_Nova::GetPosition()
	{
		return _xy;
	}

	int* Skill_Shock_Nova::GetHitbox()
	{
		return _hitbox;
	}


}