void bhkProxyObject::BuildColBox()
{
	Box3 box; box.Init();
	for (int i = 0;i < pblock2->Count(PB_MESHLIST); i++) {
		INode *tnode = NULL;
		pblock2->GetValue(PB_MESHLIST,0,tnode,FOREVER,i);	
		if (tnode)
		{
			ObjectState os = tnode->EvalWorldState(0);
			Matrix3 wm = tnode->GetNodeTM(0);
			TriObject *tri = (TriObject *)os.obj->ConvertToType(0, Class_ID(TRIOBJ_CLASS_ID, 0));
			if (tri)
			{
				Box3 box2; box2.Init();
				Mesh& mesh = tri->GetMesh();
				CalcAxisAlignedBox(mesh, box2, &wm);
				box += box2;
			}
		}
	}
	BuildBox(proxyMesh, box.Max().y-box.Min().y, box.Max().x-box.Min().x, box.Max().z-box.Min().z);

	MNMesh mn(proxyMesh);
	Matrix3 tm(true);
	tm.SetTranslate(box.Center());
	mn.Transform(tm);
	mn.OutToTri(proxyMesh);

	//proxyPos = box.Center();
	proxyPos = Point3::Origin;
	forceRedraw = true;
}