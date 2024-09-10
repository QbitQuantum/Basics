Vec3D CTerrainData::getVertexNormal(int nCellX, int nCellY)const
{
	float a = getVertexHeight(nCellX,	nCellY);
	float b = getVertexHeight(nCellX,	nCellY+1);
	float c = getVertexHeight(nCellX+1,	nCellY);
	Vec3D vVector0(0,(b-a),1);
	Vec3D vVector1(1,(c-a),0);
	Vec3D vN = vVector0.cross(vVector1);
	return vN.normalize();
}