static void _buildTriangleTabForVertices(CTriangleListItem **pVertex, const int nv, const int *ptri, const int ntri, const int nstep, CMemoryMgr &mgr)
{
	int i, j;
	for (i=0; i<nv; i++) pVertex[i]=NULL;
	for (i=0; i<ntri; i++){
		const int* a = &ptri[i*nstep];
		for (j=0; j<nstep; j++){
			const int v0 = a[j];
			CTriangleListItem * pListItem = (CTriangleListItem*)mgr.Malloc(sizeof(CTriangleListItem));
			pListItem->m_nTriangleID = i;
			pListItem->m_pNext = pVertex[v0];
			pVertex[v0] = pListItem;
		}
	}
}