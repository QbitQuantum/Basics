ICreature* CMapFileIO::LoadCreature(XML_MANAGER_HANDLE xml, XML_NODE_HANDLE hCreNode) const
{
	ICreature* pCrt = 0;
	CSampleMobAnimator* pMa = 0;

	LPWSTR type = GetNodeAttr(xml, hCreNode, L"type");
	if(!type)
		return 0;
	LPWSTR name = GetNodeAttr(xml, hCreNode, L"name");
	if(!name)
		return 0;
	LPWSTR src = GetNodeAttr(xml, hCreNode, L"source");
	if(!src)
		return 0;

	//deleted at LittleMap.cpp
	pCrt = CCreatureManager::GetInstance().CreateCreature(type, name, src);
	_ASSERT( pCrt!=NULL );
	if( !pCrt )
		return NULL;

	//deleted at Creature's destructor
	pMa = CCreatureManager::GetInstance().CreateAnimator(type, name, src);
	pCrt->SetAnimatorRef(pMa);
	pCrt->SetName(name);

	//position
	XML_NODE_HANDLE sub = RetrieveNode(xml, hCreNode, L"Location");
	if(!sub)
		return 0;
	XML_NODE_HANDLE sub1 = RetrieveNode(xml, sub, L"position");
	LPWSTR xt = GetNodeAttr(xml, sub1, L"x");
	if(!xt)
		return 0;
	LPWSTR yt = GetNodeAttr(xml, sub1, L"y");
	if(!yt)
		return 0;
	LPWSTR zt = GetNodeAttr(xml, sub1, L"z");
	if(!zt)
		return 0;
	float x = (float)_wtof(xt);
	float y = (float)_wtof(yt);
	float z = (float)_wtof(zt);
	D3DXVECTOR3 pos = D3DXVECTOR3(x, y, z);

	pCrt->SetPosition(pos);

	ReleaseNode(sub);
	ReleaseNode(sub1);
	ReleaseTextString(name);
	ReleaseTextString(type);
	ReleaseTextString(src);
	ReleaseTextString(xt);
	ReleaseTextString(yt);
	ReleaseTextString(zt);

	return pCrt;
}