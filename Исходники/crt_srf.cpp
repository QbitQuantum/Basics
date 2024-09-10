int
APITestUtil::MakeTestMirrorSurface(NURBSSet &nset, int p)
{
	NURBSMirrorSurface *s = new NURBSMirrorSurface();
	s->SetName(GetString(IDS_MIRROR_SURFACE));
	s->SetNSet(&nset);

	s->SetParent(p);
	Matrix3 mat;
	mat.IdentityMatrix();
	s->SetXForm(0, mat);
	s->SetAxis(kMirrorZ);
	s->SetDistance(0, 100.0);
	s->FlipNormals(TRUE);
	return nset.AppendObject(s);
}