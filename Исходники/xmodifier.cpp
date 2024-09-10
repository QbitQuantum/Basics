int  XTCSample::DisplayMesh(TimeValue t, INode* inode, ViewExp *vpt, int flags, Mesh *mesh)
{
	if ( ! vpt || ! vpt->IsAlive() )
	{
		// why are we here
		DbgAssert(!_T("Doing DisplayMesh() on invalid viewport!"));
		return FALSE;
	}

	if(!bFN_OnOff && !bFA_OnOff)
		return 0;

	if(!mesh)
		return 0;

	Interval ivalid = FOREVER;

	GraphicsWindow *gw = vpt->getGW();
	gw->setTransform(inode->GetObjectTM(t));
	DWORD oldMode = gw->getRndLimits();
	gw->setRndLimits(oldMode|GW_ILLUM);

	if(bFN_OnOff)
	{
		mesh->checkNormals(TRUE);	
		Point3 pt[3];
		Point3 rgb[3];
		int edges[3] = {GW_EDGE_VIS,GW_EDGE_VIS,GW_EDGE_VIS};
		gw->setColor(LINE_COLOR, (float)0.0, (float)0.0, (float)0.8);
		rgb[0] = Point3((float)0.0, (float)0.0, (float)0.8);
		rgb[1] = Point3((float)1.0, (float)1.0, (float)1.0);
		for(int i = 0; i < mesh->getNumFaces(); i++) {
			pt[0] = (mesh->getVert(mesh->faces[i].v[0]) + mesh->getVert(mesh->faces[i].v[1]) + mesh->getVert(mesh->faces[i].v[2]))/3.0f;
			pt[1] = pt[0] + mesh->getFaceNormal(i) * size;
			gw->polyline(2, pt,rgb, NULL, 0, edges);
		}
	}
	
	if(bFA_OnOff)
	{
		float faceArea;
		bo->GetParamBlockByID(x_params)->GetValue(pb_fa_spin,t,faceArea, ivalid);
		BitArray ba;
		ba.SetSize(mesh->getNumFaces());
		Point3 vtx[4];
		Point3 col[4];
		
		for(int i = 0 ; i < mesh->getNumFaces() ; i++ )
		{
			Point3 va = mesh->verts[mesh->faces[i].v[1]]-mesh->verts[mesh->faces[i].v[0]];
			Point3 vb = mesh->verts[mesh->faces[i].v[2]]-mesh->verts[mesh->faces[i].v[1]];
			Point3 vc = mesh->verts[mesh->faces[i].v[0]]-mesh->verts[mesh->faces[i].v[2]];

			float CosAngleC = DotProd(va,vb)/(Length(va)*Length(vb));
			float area = 0.5f*Length(va)*Length(vb)*sin(acos(CosAngleC));;
			float edgeLength = Length(va)+Length(vb)+Length(vc);

			if(area/(edgeLength*edgeLength) < faceArea/100.0f)
			{
				vtx[0] = mesh->verts[mesh->faces[i].v[0]];
				vtx[1] = mesh->verts[mesh->faces[i].v[1]];
				vtx[2] = mesh->verts[mesh->faces[i].v[2]];
				col[0] = col[1] = col[2] = col[3] = Point3(1,0,0);
				gw->polygon(3, vtx, col, NULL);
			}		
		}
	}

	gw->setRndLimits(oldMode);

	return 0;		
}