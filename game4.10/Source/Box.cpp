#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Box.h"

namespace game_framework {
	Box::Box() {
		Initialize();
	}

	void Box::Initialize() 
	{
		ani_offense.SetDelayCount(2);
		ani_defense.SetDelayCount(2);
		ani_misc.SetDelayCount(2);
		category_flag = 0;
		item_flag_x = 0;
		item_flag_y = 0;
		isOpened = isOpendOffense = isOpendDefense = isOpendMisc = false;
	}
	void Box::LoadBitmap()
	{	
		bm_board.LoadBitmap(BOX_BOARD, RGB(50, 255, 0));

		int m1[5] = { BOX_OFFENSE_01,BOX_OFFENSE_02,BOX_OFFENSE_03,BOX_OFFENSE_04,BOX_OFFENSE_05 };
		for (int i = 0; i < 5; i++)
			ani_offense.AddBitmap(m1[i], RGB(50, 255, 0));

		int m2[5] = { BOX_DEFENSE_01,BOX_DEFENSE_02,BOX_DEFENSE_03,BOX_DEFENSE_04,BOX_DEFENSE_05 };
		for (int i = 0; i < 5; i++)
			ani_defense.AddBitmap(m2[i], RGB(50, 255, 0));

		int m3[5] = { BOX_MISC_01,BOX_MISC_02,BOX_MISC_03,BOX_MISC_04,BOX_MISC_05 };
		for (int i = 0; i < 5; i++)
			ani_misc.AddBitmap(m3[i], RGB(50, 255, 0));

		bm_item_board.LoadBitmap(BOX_ITEM_BOARD, RGB(50, 255, 0));
		bm_cursor.LoadBitmap(BOX_CURSOR, RGB(50, 255, 0));
		bm_offense_text.LoadBitmap(BOX_TEXT_OFFENSE, RGB(50, 255, 0));
		bm_defense_text.LoadBitmap(BOX_TEXT_DEFENSE, RGB(50, 255, 0));
		bm_misc_text.LoadBitmap(BOX_TEXT_MISC, RGB(50, 255, 0));
		bm_unknown_item.LoadBitmap(ITEM_UNKNOWN, RGB(50, 255, 0));

		bm_board.SetTopLeft(50, 70);
		bm_item_board.SetTopLeft(50, 70);
		bm_offense_text.SetTopLeft(70, 95);
		bm_defense_text.SetTopLeft(70, 95);
		bm_misc_text.SetTopLeft(70, 95);
		bm_cursor.SetTopLeft(75,133);

		ani_offense.SetTopLeft(50, 70);
		ani_defense.SetTopLeft(50, 70);
		ani_misc.SetTopLeft(50, 70);

	}

	void Box::OnMove(vector<Item*> item)
	{
		if (isOpendOffense || isOpendDefense || isOpendMisc)		//開第二層
		{
			temp_item = item;
			bm_cursor.SetTopLeft(75 + item_flag_x * ITEM_X, 133 + item_flag_y * ITEM_Y);
		}
		else if (isOpened)											//開第一層
		{
			switch (category_flag)
			{
			case 0:
				if (!ani_offense.IsFinalBitmap())
					ani_offense.OnMove();
				break;
			case 1:
				if (!ani_defense.IsFinalBitmap())
					ani_defense.OnMove();
				break;
			case 2:
				if (!ani_misc.IsFinalBitmap())
					ani_misc.OnMove();
				break;
			default:
				break;
			}
		}
	}
	
	void Box::OnShow()
	{
		if (isOpendOffense || isOpendDefense || isOpendMisc)
		{
			bm_item_board.ShowBitmap();
			int row = 0, col = 0;
			switch (category_flag)
			{
			
			case 0:
				bm_offense_text.ShowBitmap();
				
				for (int i = 0; i < temp_item.size(); i++)
				{
					if (temp_item[i]->GetType() == "OFFENSE")
					{
						if (row == 6) {
							row = 0;
							col++;
						}

						if (temp_item[i]->HaveItem()) {
							temp_item[i]->SetXY(76 + 40 * row, 130 + 40 * col);
							temp_item[i]->OnShow();
							row++;
						}
						else {
							bm_unknown_item.SetTopLeft(76 + 40 * row, 130 + 40 * col);
							bm_unknown_item.ShowBitmap();
							row++;
						}
					}
				}
				temp_item.clear();
				break;
			case 1:
				bm_defense_text.ShowBitmap();

				for (int i = 0; i < temp_item.size(); i++)
				{
					if (temp_item[i]->GetType() == "DEFENSE")
					{
						if (row == 6) {
							row = 0;
							col++;
						}

						if (temp_item[i]->HaveItem()) {
							temp_item[i]->SetXY(76 + 40 * row, 130 + 40 * col);
							temp_item[i]->OnShow();
							row++;
						}
						else {
							bm_unknown_item.SetTopLeft(76 + 40 * row, 130 + 40 * col);
							bm_unknown_item.ShowBitmap();
							row++;
						}
					}
				}
				temp_item.clear();
				break;

			case 2:
				bm_misc_text.ShowBitmap();

				for (int i = 0; i < temp_item.size(); i++)
				{
					if (temp_item[i]->GetType() == "MISC")
					{
						if (row == 6) {
							row = 0;
							col++;
						}

						if (temp_item[i]->HaveItem()) {
							temp_item[i]->SetXY(76 + 40 * row, 130 + 40 * col);
							temp_item[i]->OnShow();
							row++;
						}
						else {
							bm_unknown_item.SetTopLeft(76 + 40 * row, 130 + 40 * col);
							bm_unknown_item.ShowBitmap();
							row++;
						}
					}
				}
				temp_item.clear();
				break;
			}

			bm_cursor.ShowBitmap();
		}
		else if (isOpened)
		{
			bm_board.ShowBitmap();
			ani_offense.OnShow();
			ani_defense.OnShow();
			ani_misc.OnShow();
		}
	}

	void Box::Down()
	{
		if (isOpendOffense || isOpendDefense || isOpendMisc)
		{
			if(item_flag_y < 3)
				item_flag_y++;
		}
		else if (category_flag < 2 && isOpened)
		{
			category_flag++;
			ani_offense.Reset();
			ani_defense.Reset();
			ani_misc.Reset();
		}
	}
	void Box::Up()
	{
		if (isOpendOffense || isOpendDefense || isOpendMisc)
		{
			if (item_flag_y > 0)
				item_flag_y--;
		}
		else if (category_flag > 0 && isOpened)
		{
			category_flag--;
			ani_offense.Reset();
			ani_defense.Reset();
			ani_misc.Reset();
		}
	}

	void Box::Open(bool openBox)
	{
		isOpened = openBox;
		if (!openBox)
		{
			ani_offense.Reset();
			ani_defense.Reset();
			ani_misc.Reset();
			category_flag =0;
		}

	}

	void Box::OpenOpen(bool openopenBox)
	{
		if (!openopenBox)
		{
			isOpendOffense = false;
			isOpendDefense = false;
			isOpendMisc = false;
			item_flag_x = 0;
			item_flag_y = 0;
		}
		else
		{
			switch (category_flag)
			{
			case 0:
				isOpendOffense = true;
				break;
			case 1:
				isOpendDefense = true;
				break;
			case 2:
				isOpendMisc = true;
				break;
			}
		}
	}

	void Box::Left()
	{
		if (item_flag_x > 0)
			item_flag_x--;
	}

	void Box::Right() 
	{
		if (item_flag_x < 5)
			item_flag_x++;
	}
}