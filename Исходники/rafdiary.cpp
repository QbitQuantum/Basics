void RAFDiary::Refresh()
{
	
	CRCombo* combo;

	combo=GETDLGITEM(IDC_RCOMBOGROUP);
	combo->Clear()->RESCOMBO(10,6)->
					SetIndex(group);

	combo=GETDLGITEM(IDC_RCOMBOSQUAD);
	combo->Clear();
	
	int index = 0;
	for (int i = 0; i < maxsquads; i++)
	{
		combo->AddString(Node_Data.squadron[Squadron[i]].SubName());
		if(sqnum == Node_Data.squadron[Squadron[i]].squadron)
			index = i;

	}

	combo->SetIndex(index);



}