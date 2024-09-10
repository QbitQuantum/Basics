static void SavePos(openfile* p)
{
	LVITEM Item;
	int n;
	p->Last[0] = 0;

	for (n=0;n<ListView_GetItemCount(p->WndList);++n)
		if (ListView_GetItemState(p->WndList,n,LVIS_FOCUSED)==LVIS_FOCUSED)
		{
			Item.iItem=n;
			Item.iSubItem = 0;
			Item.mask=LVIF_PARAM;
			ListView_GetItem(p->WndList,&Item);

			if (Item.lParam)
				tcscpy_s(p->Last,TSIZEOF(p->Last),((openitem*)Item.lParam)->Name);

			break;
		}
}