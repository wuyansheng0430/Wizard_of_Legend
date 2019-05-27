#ifndef CHARACTER_H
#define CHARACTER_H
#include "GameMap.h"
#include "CharacterData.h"
#include "Layer.h"

namespace game_framework {

	enum DIRECTION {
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	class Character : public Layer {
	public:
		Character();
		void Initialize(int*);							//重製角色座標、數據
		void LoadBitmap();								//載入動畫、圖片
		void OnMove(GameMap *);							//傳入地圖用以判斷所處位置
		void OnShow();									//顯示
		void SetMovingDown(bool flag);					//往下移動
		void SetMovingLeft(bool flag);					//往左移動
		void SetMovingRight(bool flag);					//往右移動
		void SetMovingUp(bool flag);					//往上移動
		void Dash();									//Dash 位移
		const int* GetHitbox();							//碰撞窗
		Skill* GenerateSkill(int, float, float);		//生成技能 (skill number, 生成座標)
		bool IsUsingSkill();							//是否正在使用技能(播放角色使用技能的動畫)
		bool IsHurt();									//是否被毆，被毆時不能用技能
	private:
		bool IsSlash();									//是否斜走
		bool CanDash();									//是否可以Dash
		bool IsMoving();								//是否有輸入任何(上下左右)移動指令
		int CaculateVector(int, int);					//計算滑鼠的 Vector，用來判定技能施放時，角色該面對的方向
		void ResetRun();
		void ResetDash();

		CAnimation _ani_up, _ani_down, _ani_left, _ani_right;												//走路動畫
		CAnimation _ani_run_up, _ani_run_down, _ani_run_left, _ani_run_right;								//跑步時的氣流
		CAnimation _ani_dash_up, _ani_dash_down, _ani_dash_left, _ani_dash_right;							//dash動畫
		//CAnimation _ani_arrival;																			//出場動畫
		//CAnimation _ani_dead;																				//死亡動畫
		CAnimation _ani_useSkill_1;																			//使用Skill 1 動畫
		CAnimation _ani_useSkill_2_up, _ani_useSkill_2_down, _ani_useSkill_2_left, _ani_useSkill_2_right;	//使用Skill 2 動畫
		CAnimation _ani_useSkill_3_down, _ani_useSkill_3_up;												//使用Skill 3 動畫
		CAnimation* _ani_useSkill;																			//暫存現在使用的技能
		CMovingBitmap _bm_stand_up, _bm_stand_down, _bm_stand_left, _bm_stand_right;						//站立圖
		CMovingBitmap _bm_hurt_left, _bm_hurt_right;														//被毆圖

		DIRECTION _direction;												// 紀錄角色面向方向
		int _dx, _dy;														//移動距離
		bool _isMovingDown, _isMovingLeft, _isMovingRight, _isMovingUp;		//移動方向
		bool _isDash;														//Dash
		bool _isRunning;													//跑步
		bool _isDashLock;													//Dash中不能改變移動方向，必須等Dash結束
		bool _isUsingSkill;													//是否正在使用技能
		bool _isHurt;														//被毆
		int _useSkillNum;
		float _step;
		int _run_counter;			// 計算角色是否要奔跑
		int _dash_delay_counter;  //讓玩家無法一直dash (dash和dash之間有間隔)
		int _dash_counter;	//用來reset dash 動畫
		double _dash_resistance;
		int _hit_recover_counter;
		int _hp;	//暫存HP，用來檢查是否扣血
	};
}

#endif