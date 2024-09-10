/// @brief 属性网格元素,获取指定项的值.
/// @param hEle  元素句柄.
/// @param itemID  项ID标示符.
/// @param pOut   接收内容缓冲区.
/// @param len    pOut缓冲区长度
void WINAPI XPGrid_GetItemValue(HELE hEle,int itemID,wchar_t *pOut,int len)
{
	IsPGridDebug(hEle,__FUNCTION__);
	propertyGrid_ *pObj=(propertyGrid_*)hEle;
	PGridItem_ *pItem=PGrid_GetItem(hEle,itemID);
	if(NULL==pItem) return;

	switch(pItem->type)
	{
	case PGRID_STRING:
		{
			wmemcpy_s(pOut,len,pItem->pValue,wcslen(pItem->pValue));
		}break;
	case PGRID_EDIT_FILE:
	case PGRID_EDIT:
		{
			if(pItem->hEle)
				XEdit_GetText(pItem->hEle,pOut,len);
		}break;
	case PGRID_COMBOBOX:
		{
			if(pItem->hEle)
				XComboBox_GetText(pItem->hEle,pOut,len);
		}break;
	case PGRID_CHOOSECOLOR:
		{
			if(len<7) return;
			wchar_t color[8]={0};
			XEdit_GetText(pItem->hEle,pOut,7);
		}break;
	}
}