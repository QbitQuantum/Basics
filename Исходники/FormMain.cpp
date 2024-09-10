//---------------------------------------------------------------------------
unsigned int __fastcall TfrmMain::CheckItem(bool isMoney ,unsigned long ItemID)
{
		if( isMoney )
		{
            return ItemID;
        }
		if (list_filter->Items->IndexOfObject((TObject *)ItemID) > -1)
		{
			return 0; // 物品在過濾清單
		}
		else if (list_drop->Items->IndexOfObject((TObject *)ItemID) > -1)
		{
			return ItemID; // 物品在掉落清單
		}
		else // 物品不在掉落清單
		{
			String name = String(GetItemName(ItemID));
			if (name.IsEmpty())
			{
				name.sprintf(TEXT(L"未知物品(編號:%d)"), ItemID);
			}
			list_drop->Items->AddObject(name, (TObject *)ItemID);
			return ItemID;
		}
}