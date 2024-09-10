/* free rows */
void Mapix::freeRows(LPSRowSet nRows)
{
	if(nRows) 
	{
		for(ULONG i=0;i<nRows->cRows;i++) 
		{
			MAPIFreeBuffer(nRows->aRow[i].lpProps);
		}
		MAPIFreeBuffer(nRows);
	}
}