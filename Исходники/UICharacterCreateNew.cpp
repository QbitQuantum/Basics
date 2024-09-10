void CUICharacterCreateNew::SetArrayList(CUIArray* pArray)
{
	CUIArrayItem* pArrayItem = NULL;

	if (pArray == NULL)
		return;

	int count = pArray->GetArrayChildCount();

	CUIText* pText;

	for (int i = 0; i < count; i++)
	{
		pArrayItem = pArray->GetArrayItem(i);

		if ( pArrayItem == NULL )
			continue;

		pText = (CUIText*)pArrayItem->findUI("str_number");

		if (pText != NULL)
		{
			CTString strNum = "";
			strNum.PrintF( "%d", i+1 );
			pText->SetText(strNum);
		}
	}
}