static Bool _DeformFn(BaseDocument *doc, BaseList2D *op, HairObject *hair, HairGuides *guides, Vector *padr, LONG cnt, LONG scnt)
{
	LONG i,l;
	BaseContainer *bc=op->GetDataInstance();

	const SReal *pCombX=NULL,*pCombY=NULL,*pCombZ=NULL;

	HairLibrary hlib;
	RootObjectData rData;
	hair->GetRootObject(NULL,NULL,&rData);

	if (!rData.pObject) return TRUE;

	Real strength=bc->GetReal(HAIR_DEFORMER_STRENGTH);

	VertexMapTag *pVTag=(VertexMapTag*)bc->GetLink(HAIR_DEFORMER_COMB_X,doc,Tvertexmap);
	if (pVTag && pVTag->GetObject()==rData.pObject) pCombX=pVTag->GetDataAddressR();

	pVTag=(VertexMapTag*)bc->GetLink(HAIR_DEFORMER_COMB_Y,doc,Tvertexmap);
	if (pVTag && pVTag->GetObject()==rData.pObject) pCombY=pVTag->GetDataAddressR();

	pVTag=(VertexMapTag*)bc->GetLink(HAIR_DEFORMER_COMB_Z,doc,Tvertexmap);
	if (pVTag && pVTag->GetObject()==rData.pObject) pCombZ=pVTag->GetDataAddressR();

	if (!(pCombX || pCombY || pCombZ)) return TRUE;

	const CPolygon *vadr=rData.pPolygon;

	if (!padr || !vadr) return TRUE;

	for (i=0;i<cnt;i++)
	{
		Vector comb,dn(DC);
		HairRootData hroot=guides->GetRoot(i);

		LONG p=hroot.m_ID;
		Real s=hroot.m_S,t=hroot.m_T;

		if (hroot.m_Type==HAIR_ROOT_TYPE_POLY)
		{
			if (pCombX) comb.x=hlib.MixST(s,t,pCombX[vadr[p].a],pCombX[vadr[p].b],pCombX[vadr[p].c],pCombX[vadr[p].d],vadr[p].c!=vadr[p].d)-0.5;
			if (pCombY) comb.y=hlib.MixST(s,t,pCombY[vadr[p].a],pCombY[vadr[p].b],pCombY[vadr[p].c],pCombY[vadr[p].d],vadr[p].c!=vadr[p].d)-0.5;
			if (pCombZ) comb.z=hlib.MixST(s,t,pCombZ[vadr[p].a],pCombZ[vadr[p].b],pCombZ[vadr[p].c],pCombZ[vadr[p].d],vadr[p].c!=vadr[p].d)-0.5;
		}
		else if (hroot.m_Type==HAIR_ROOT_TYPE_VERTEX)
		{
			if (pCombX) comb.x=pCombX[p];
			if (pCombY) comb.y=pCombX[p];
			if (pCombZ) comb.z=pCombX[p];
		}
		else
			continue;

		dn=!(padr[i*scnt+1]-padr[i*scnt]);

		Real cs=Len(comb)*strength;
		if (Abs(cs)<1e-5) continue;
		
		comb=comb/cs;
		dn=!Mix(dn,comb,cs);

		Vector ax=comb%dn;
		Real theta=dn*comb;

		Matrix tm=RotAxisToMatrix(ax,theta);

		for (l=1;l<scnt;l++)
		{
			padr[i*scnt+l]=((padr[i*scnt+l]-padr[i*scnt])^tm)+padr[i*scnt];
		}
	}

	return TRUE;
}