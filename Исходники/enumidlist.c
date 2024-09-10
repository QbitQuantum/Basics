/**************************************************************************
*   DeleteList()
*/
static BOOL DeleteList(
	IEnumIDList * iface)
{
	IEnumIDListImpl *This = (IEnumIDListImpl *)iface;

	LPENUMLIST  pDelete;

	TRACE("(%p)->()\n",This);

	while(This->mpFirst)
	{ pDelete = This->mpFirst;
	  This->mpFirst = pDelete->pNext;
	  SHFree(pDelete->pidl);
	  SHFree(pDelete);
	}
	This->mpFirst = This->mpLast = This->mpCurrent = NULL;
	return TRUE;
}