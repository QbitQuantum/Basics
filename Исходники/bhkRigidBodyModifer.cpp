void bhkRigidBodyModifier::BuildColBox(Mesh& mesh)
{
	Box3 box; box.Init();
	CalcAxisAlignedBox(mesh, box, NULL);
	BuildBox(mesh, box.Max().y-box.Min().y, box.Max().x-box.Min().x, box.Max().z-box.Min().z);

	MNMesh mn(mesh);
	Matrix3 tm(true);
	tm.Translate(box.Center());
	mn.Transform(tm);
	mn.OutToTri(mesh);
}