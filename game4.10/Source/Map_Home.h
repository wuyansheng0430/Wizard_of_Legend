#ifndef MAP_HOME_H
#define MAP_HOME_H
#include "GameMap.h"
#include "Character.h"

namespace game_framework {
	class Map_Home : public GameMap {
		enum AREA {
			AREA_1
		};
	public:
		Map_Home(int, int);  // 設定初始中心點
		~Map_Home();
		void AddEnemy() override;
		void LoadBitmap();
		void OnMove();
		int GetMapStatus(float, float);	
	};
}
#endif