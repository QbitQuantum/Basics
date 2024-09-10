inline bool computeSDFNormal(const UT_VoxelArrayF *g_col, int iX, int iY, int iZ, vector3 &norm){
	//Make sure this is a border cell?????
	if (g_col->getValue(iX, iY, iZ) <= 0)
		return false;
	norm[0] = g_col->getValue(iX-1,iY,iZ) - g_col->getValue(iX+1,iY,iZ);
	norm[1] = g_col->getValue(iX,iY-1,iZ) - g_col->getValue(iX,iY+1,iZ);
	norm[2] = g_col->getValue(iX,iY,iZ-1) - g_col->getValue(iX,iY,iZ+1);
	norm.normalize();
	return true;
}