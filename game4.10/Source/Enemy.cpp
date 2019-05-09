#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include <cmath>
#include "audio.h"
#include "gamelib.h"
#include "Enemy.h"
#include "Map_Home_Logic.h"

#define CHARGING_ZONE 300

namespace game_framework {
	Enemy::Enemy(int x, int y, int area, int zone) : _ori_x(x), _ori_y(y), _area(area), _zone(zone)
	{
		Initialize(x, y);
	}

	Enemy::~Enemy(){}

	void Enemy::Initialize(int x, int y)
	{
		_xy[0] = x;
		_xy[1] = y;
		_is_detour = _is_left = _is_right = _is_up = _is_down = false;
		_detour_time = 0;
		_is_x_arrive = _is_y_arrive = false;
		_state = NOTHING;
		_get_hurt = false;
		_get_hurt_counter = 0;
		_attack_counter = 0;
		_hp = 100;
		_step = 20;
		_zone = 30;
		_damage = 10;
		
		for (int i = 0; i < 4; i++)
			_neighbor[i] = true;
	}

	void Enemy::LoadBitmap()
	{
		LoadBitmap_2();

		int ani[7] = { GET_HURT_01, GET_HURT_02, GET_HURT_03, GET_HURT_04, GET_HURT_05, GET_HURT_06, GET_HURT_07 };
		for (int i = 0; i < 7; i++)
			_ani_hurt.AddBitmap(ani[i], RGB(50, 255, 0));

		_ani_hurt.SetDelayCount(1);

		
	}

	void Enemy::OnMove(int cx, int cy, vector<Skill*> &skills)
	{
		
		if (_hp > 0)
		{
			int currentX = _xy[0];
			int currentY = _xy[1];

			_get_hurt_counter != 0 ? _get_hurt_counter-- : NULL;
			
			if (pow(_xy[0] - _ori_x, 2) + pow(_xy[1] - _ori_y, 2) > pow(CHARGING_ZONE, 2) && _state != HIT_RECOVER)
			{
				_state = RESET;
			}
			
			// �ޯ�I���P�w
			
			std::vector<Skill*>::iterator iter;
			for (iter = skills.begin(); iter != skills.end(); iter++)
			{
				int ori_hp = _hp;
				_hp -= (*iter)->GetDamage(this);
				if (_hp != ori_hp)
				{
					_get_hurt = true;
					//_pre_state = _state;
					_state = HIT_RECOVER;
				}
			}
			

			//�۰ʴM��
			switch (_state)
			{
			case CHARGING:
				MoveToTarget(cx, cy);
				//_target_x = cx;
				//_target_y = cy;
				break;

			case RESET:
				MoveToTarget(_ori_x, _ori_y);
				//_target_x = _ori_x;
				//_target_y = _ori_y;
				break;
			
			case ATTACKING:
				break;

			case NOTHING:
				break;

			case HIT_RECOVER:
				break;
			}

			_attack_counter > 0 ? _attack_counter-- : NULL;

			Move(CHARACTER_SCREEN_X + _xy[0] - cx, CHARACTER_SCREEN_Y + _xy[1] - cy);

			

		}

			
	}

	void Enemy::SetXY(int x, int y)
	{
		_xy[0] += x;
		_xy[1] += y;
	}
	

	int* Enemy::GetPosition() 
	{
		return _xy;
	}

	int* Enemy::GetCollisionMove() 
	{
		return _collision_move;
	}

	int *Enemy::GetHitbox()
	{
		return _hitbox;
	}
	
	bool Enemy::CanAchieved(int dx, int dy)
	{
		int x1 = _xy[0] + _collision_move[0];
		int y1 = _xy[1] + _collision_move[1];
		int x2 = x1 + _collision_move[2];
		int y2 = y1 + _collision_move[3];
		if ((HOME_LOGIC[x1 + dx][y1 + dy] != -1) &&
			(HOME_LOGIC[x2 + dx][y1 + dy] != -1) &&
			(HOME_LOGIC[x1 + dx][y2 + dy] != -1) &&
			(HOME_LOGIC[x2 + dx][y2 + dy] != -1))
		{
			return true;
		}
		return false;
	}

	bool Enemy::IsLive()
	{
		return _hp > 0;
	}

	void Enemy::NotifyCharge()
	{
		if(_state != HIT_RECOVER)
			_state = CHARGING;
	}

	int Enemy::Area()
	{
		return _area;
	}

	void Enemy::MoveToTarget(int target_x, int target_y)
	{
		int currentX = _xy[0];
		int currentY = _xy[1];
		int midX = _xy[0] + (_collision_move[0] + _collision_move[2]) / 2;
		int midY = _xy[1] + 3 * (_collision_move[1] + _collision_move[3]) / 4;
		int cMidX = target_x + 35;
		int cMidY = target_y + 35;


		if (!_is_detour)
		{
			int temp_step = _step;

			if ((abs(midX - cMidX) > _zone) && (abs(midY - cMidY) > _zone))
				temp_step = (float)(_step) * 0.6 + 0.5;

			if ((abs(midX - cMidX) > _zone))
			{
				_is_x_arrive = false;
				if (midX > cMidX)
				{
					if (CanAchieved(-temp_step, 0))
					{
						_direction = LEFT;
						_xy[0] -= temp_step;
					}
					else
					{
						_neighbor[2] = false;
					}
				}
				else if (midX < cMidX)
				{
					if (CanAchieved(temp_step, 0))
					{
						_direction = RIGHT;
						_xy[0] += temp_step;
					}
					else
					{
						_neighbor[3] = false;
					}
				}
			}
			else
			{
				_is_x_arrive = true;
			}

			if ((abs(midY - cMidY) > _zone))
			{
				_is_y_arrive = false;
				if (midY > cMidY)
				{
					if (CanAchieved(0, -temp_step))
					{
						_xy[1] -= temp_step;
					}
					else
					{
						_neighbor[0] = false;
					}
				}
				else if (midY < cMidY)
				{
					if (CanAchieved(0, temp_step))
					{
						_xy[1] += temp_step;
					}
					else
					{
						_neighbor[1] = false;
					}
				}
			}
			else
			{
				_is_y_arrive = true;
			}
		}
		else
		{
			if (_is_up)
			{
				
				CanAchieved(0, -_step) ? _xy[1] -= _step : NULL;
			}
			else if (_is_down)
			{
				CanAchieved(0, _step) ? _xy[1] += _step : NULL;
			}
			else if(_is_left)
			{
				_direction = LEFT;
				CanAchieved(-_step, 0) ? _xy[0] -= _step : NULL;
			}
			else if (_is_right)
			{
				_direction = RIGHT;
				CanAchieved(_step, 0) ? _xy[0] += _step : NULL;
			}

			_detour_time--;

			if (_detour_time <= 0)
			{
				_is_detour = false;

				for (int i = 0; i < 4; i++)
				{
					_neighbor[i] = true;
				}
				_is_left = false;
				_is_right = false;
				_is_up = false;
				_is_down = false;
			}
		}
		if ((currentX == _xy[0]) && (currentY == _xy[1]) && ((!_is_x_arrive) || (!_is_y_arrive)))
		{
			_is_detour = true;
			if (_neighbor[0] == false)	//�W�d��
			{
				for (int i = 0; i < 60; i++)
				{
					//�V�k�ˬd
					if (CanAchieved(_step * (i + 1), 0))
					{
						if (CanAchieved(_step * (i + 1), -_step))
						{
							_detour_time = i;
							_is_right = true;
							break;
						}
					}
					//�V���ˬd
					if (CanAchieved(-_step * (i + 1), 0))
					{
						if (CanAchieved(-_step * (i + 1), -_step))
						{
							_detour_time = i;
							_is_left = true;
							break;
						}
					}
				}
			}
			if (_neighbor[1] == false)	//�U�d��
			{
				
				for (int i = 0; i < 60; i++)
				{
					//�V�k�ˬd
					if (CanAchieved(_step * (i + 1), 0))
					{
						if (CanAchieved(_step * (i + 1), _step))
						{
							_is_right = true;
							_detour_time = i;
							break;
						}
					}
					//�V���ˬd
					if (CanAchieved(-_step * (i + 1), 0))
					{
						if (CanAchieved(-_step * (i + 1), _step))
						{
							_detour_time = i;
							_is_left = true;
							break;
						}
					}
				}
			}

			if (_neighbor[2] == false)	//���d��
			{
				for (int i = 0; i < 60; i++)
				{
					//�V�W�ˬd
					if (CanAchieved(0 , -_step * (i + 1)))
					{
						if (CanAchieved(-_step , -_step * (i + 1)))
						{
							_detour_time = i;
							_is_up = true;
							break;
						}
					}
					//�V�U�ˬd
					if (CanAchieved(0, _step * (i + 1)))
					{
						if (CanAchieved(-_step, _step * (i + 1)))
						{
							_detour_time = i;
							_is_down = true;
							break;
						}
					}
				}
			}

			if (_neighbor[3] == false)	//�k�d��
			{		
				for (int i = 0; i < 60; i++)
				{
					//�V�W�ˬd
					if (CanAchieved(0, -_step * (i + 1)))
					{
						if (CanAchieved(_step, -_step * (i + 1)))
						{
							_detour_time = i;
							_is_up = true;
							break;
						}
					}
					//�V�U�ˬd
					if (CanAchieved(0, _step * (i + 1)))
					{
						if (CanAchieved(_step, _step * (i + 1)))
						{
							_detour_time = i;
							_is_down = true;
							break;
						}
					}
				}
			}

			
		}

		/*
		if (_state == RESET && (currentX == _xy[0]) && (currentY == _xy[1]) && _state != HIT_RECOVER)
			_state = NOTHING;

		if (_state == CHARGING && (currentX == _xy[0]) && (currentY == _xy[1]) && _state != HIT_RECOVER)
			_state = ATTACKING;
		*/

		if (_state == RESET && (currentX == _xy[0]) && (currentY == _xy[1]) && _state != HIT_RECOVER)
			_state = NOTHING;

		if (_state == CHARGING && (currentX == _xy[0]) && (currentY == _xy[1]) && _state != HIT_RECOVER)
			_attack_counter == 0 ? _state = ATTACKING : NULL;
	}

}