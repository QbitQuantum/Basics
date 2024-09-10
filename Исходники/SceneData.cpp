Vec3D CSceneData::getVertexNormal(int x, int y)const
{
	float a = getVertexHeight(x,	y);
	float b = getVertexHeight(x,	y+1);
	float c = getVertexHeight(x+1,	y);
	Vec3D vVector0(0,(b-a),1);
	Vec3D vVector1(1,(c-a),0);
	Vec3D vN = vVector0.cross(vVector1);
	return vN.normalize();
}