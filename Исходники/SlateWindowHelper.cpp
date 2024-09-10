void FSlateWindowHelper::RemoveWindowFromList( TArray<TSharedRef<SWindow>>& Windows, const TSharedRef<SWindow>& WindowToRemove )
{
	int32 NumRemoved = Windows.Remove(WindowToRemove);

	if (NumRemoved == 0)
	{
		for (int32 ChildIndex=0; ChildIndex < Windows.Num(); ++ChildIndex)
		{
			RemoveWindowFromList(Windows[ChildIndex]->GetChildWindows(), WindowToRemove) ;
		}	
	}
}