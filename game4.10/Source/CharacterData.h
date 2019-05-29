#ifndef CHARACTERDATA_H
#define	CHARACTERDATA_H

namespace game_framework {
	class CharacterData
	{
	public:
		static int Money;
		static int Diamond;
		static int HP;
		static int Max_HP;
		static int MP;
		static int Max_MP;
		static double Attack_Coefficient;
		static double Defense_Coefficient;
		static int Blood_Suck_Coefficient;	//吸血係數
		static double Move_Coefficient;	//移動速度係數
		static double CD_Coefficient;	//技能冷卻係數
		static int MP_Charge_Coefficient;	//MP累積係數
		static bool INVINCIBLE;			//Dash 時無敵
		//static void InitializeStatus();

		//static bool IsEquiped_Item[];
		//static bool IsOwned_Item[];
	};
}

#endif