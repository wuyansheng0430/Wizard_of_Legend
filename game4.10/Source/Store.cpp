#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Store.h"

namespace game_framework {

	Store::Store()
	{
		Initialize();
	}

	void Store::Initialize() {
		isItemSoldOut[0] = false;
		isItemSoldOut[1] = false;
		isItemSoldOut[2] = false;
	}

	void Store::LoadBitmap()
	{
		bm_sold_out.LoadBitmap(ITEM_SOLD_OUT, RGB(50, 255, 0));
	}

	bool Store::Buy(int number, Items *gitem)
	{
		srand((unsigned int)time(NULL));

		int item_1, item_2, num = number;

		switch (num)
		{
		case 0:
			item_1 = 1;
			item_2 = 2;
			break;
		case 1:
			item_1 = 0;
			item_2 = 2;
			break;
		case 2:
			item_1 = 0;
			item_2 = 1;
			break;
		}


		if (store_item[num]->BuyItem()) {
			int r;

			if (gitem->GetItemInStore().size() > 2) {
				r = rand() % gitem->GetItemInStore().size();

				while (store_item[item_1]->GetNumber() == gitem->GetItemInStore()[r]->GetNumber() || store_item[item_2]->GetNumber() == gitem->GetItemInStore()[r]->GetNumber())
					r = rand() % gitem->GetItemInStore().size();

				store_item.erase(store_item.begin() + num);
				store_item.insert(store_item.begin() + num, gitem->GetItemInStore()[r]);
			}
			else
				isItemSoldOut[num] = true;

			return true;
		}
		else
			return false;
	}

	void Store::Shelf(Items *gitem)
	{

		if (gitem->GetItemInStore().size() > 0) {
			srand((unsigned int)time(NULL));	//�üƺؤl
			store_item.clear();
			int r;
			for (int i = 0; i < 3; i++) {
				r = rand() % gitem->GetItemInStore().size();

				for (int j = 0; j < i; j++) {
					if (store_item[j]->GetNumber() == gitem->GetItemInStore()[r]->GetNumber()) {
						r = rand() % gitem->GetItemInStore().size();
						j = 0;
					}
				}
				store_item.push_back(gitem->GetItemInStore()[r]);
			}
		}
	}

	void Store::SetXY(int *cxy)
	{
		store_item[0]->SetXY(285 + 525 - cxy[0], 205 + 990 - cxy[1]);
		store_item[1]->SetXY(285 + 575 - cxy[0], 205 + 990 - cxy[1]);
		store_item[2]->SetXY(285 + 620 - cxy[0], 205 + 990 - cxy[1]);
	}

	void Store::OnShow(int *cxy)
	{
		
		isItemSoldOut[0] ? NULL : store_item[0]->OnShow();
		isItemSoldOut[1] ? NULL : store_item[1]->OnShow();
		isItemSoldOut[2] ? NULL : store_item[2]->OnShow();
		
		
		if (store_item[0]->HaveItem()) {
			bm_sold_out.SetTopLeft(285 + 520 - cxy[0], 205 + 1018 - cxy[1]);
			bm_sold_out.ShowBitmap();
		}
		if (store_item[1]->HaveItem()) {
			bm_sold_out.SetTopLeft(285 + 569 - cxy[0], 205 + 1018 - cxy[1]);
			bm_sold_out.ShowBitmap();
		}
		if (store_item[2]->HaveItem()) {
			bm_sold_out.SetTopLeft(285 + 618 - cxy[0], 205 + 1018 - cxy[1]);
			bm_sold_out.ShowBitmap();
		}
		
	}

	
}

