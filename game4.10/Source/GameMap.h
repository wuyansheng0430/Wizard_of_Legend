#include "Map_Home_Logic.h"
namespace game_framework {

	class GameMap {
	public:
		GameMap(int, int);  // 設定初始中心點
		~GameMap();
		void Initialize(int, int);
		void LoadBitmap();
		void OnMove();
		void OnShowBackground();
		void OnShowWall();
		void SetCharacterXY(int, int);

	private:
		Map_Home_Logic _map;	//邏輯圖層
		CMovingBitmap _background; //背景圖
		CMovingBitmap _wall; //牆
		int _cx, _cy;  //角色所在Map的座標
		const int collision_move[4] = {3,4,0,1};   //(x,y,l,w) collision_move	碰撞判定範圍
		const int collision_damage[4] = {0};	//受到傷害判定範圍
		const int CHARACTER_SCREEN_X = 285;
		const int CHARACTER_SCREEN_Y = 205;
	};

}