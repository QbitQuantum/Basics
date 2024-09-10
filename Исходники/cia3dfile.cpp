static void _insertTriangle(const Vector3i & tri, CTriangleListItem** plist, CMemoryMgr& mgr)
{
	int v0, v1, v2;
	v0 = _MIN3_(tri.x, tri.y, tri.z);
	if (v0==tri.x) v1=tri.y, v2=tri.z;
	else if (v0==tri.y) v1=tri.z, v2=tri.x;
	else v1=tri.x, v2=tri.y;

	CTriangleListItem* p = _searchTriangle(v1, v2, plist[v0]);
	if (p){
		p->m_v0=p->m_v1=-1;
		return;
	}

	CTriangleListItem * pListItem = (CTriangleListItem*)mgr.Malloc(sizeof(CTriangleListItem));
	pListItem->m_v0 = v1;
	pListItem->m_v1 = v2;
	pListItem->m_pNext = plist[v0];
	plist[v0] = pListItem;
}