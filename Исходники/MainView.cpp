void CMainView::ChangeItemSubtitle(TInt aIndex,TDes16& aText)
	{
	TInt b=iMain->ListBox()->Model()->NumberOfItems();
	TBuf<255> prev = iMain->ListBox()->Model()->ItemText(aIndex);
	TChar a = '\t'; 
	TInt pos = prev.LocateReverse(a); 
	if (pos != KErrNotFound) 
		{	 
    TInt replace_length = prev.Length() - pos;
    prev.Delete(pos+1, replace_length); 
    prev.Insert(pos+1, aText); 
		}
	CDesCArray* itemArray = static_cast<CDesCArray*> (iMain->ListBox()->Model()->ItemTextArray());
	itemArray->Delete(aIndex);
	itemArray->InsertL(aIndex,prev);
	iMain->ListBox()->DrawNow();
	}