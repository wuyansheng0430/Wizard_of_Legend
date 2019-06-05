#ifndef ITEM_H
#define ITEM_H

namespace game_framework {
	 
	enum ITEM_NUMBER
	{
		Amulet = 1,		//分裂的護身符
		Helmet,			//狂怒頭盔
		Heart,			//巨人之心
		Glasses,		//吸血鬼眼鏡
		Shoes,			//水銀的便鞋
		Pendulum,		//羅素的鐘擺
		Pocket_Watch	//托茲的懷表
	};

	class Item {
	public:
		Item(int, int, string, enum ITEM_NUMBER, int, bool (*) (), void (*) ());		//item圖片, item說明圖片, 種類, 編號, 錢, 效果
		void Initialize();
		void LoadBitmap();
		void SetXY(int, int);
		void OnShow();
		void Equip(bool);							// 穿/脫 裝備
		bool IsEquiped();							// 是否裝備
		void Effect();								// 啟動能力
		bool OwnedItem();
		bool BuyItem();
		string GetType();
		int GetNumber();
		void SetItem(bool);							//用來回復Item狀態(讀檔、離開關卡)
		void ShowInfo(int, int);					//顯示Item的效果說明
	private:
		bool (*_Launched)();						//檢查是否滿足發動條件，滿足就發動，回傳true；不滿足不做事，回傳false
		void (*_Stripping)();						//解除裝備時若有發動效果則要執行此函式解除效果
		CMovingBitmap _bm_item;
		CMovingBitmap _bm_info;
		string _type;								//item 種類
		enum ITEM_NUMBER _number;					//item 編號
		bool _isEquiped;							//是否裝備
		bool _isLuanched;							//發動
		bool _isOwned;								//擁有該裝備
		int _diamond;
		int _pic;									//暫存圖片編號，等LoadBitmap時再匯入圖片
		int _info_pic;	
	};
}
#endif