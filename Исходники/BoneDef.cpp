BOOL CBoneDef::SetInitTM(IPhysiqueExport* pExport, const Matrix3& matMesh)
{
	BOOL bErr = false;
	R_ASSERT(pBone);
	R_ASSERT(Helper::IsBone(pBone,U.m_SkinAllowDummy));
	Matrix3 tmp;
	//Log("SetInitTM:",pBone->GetName());
	if(Helper::IsBipedBone(pBone))	{
		Helper::SetBipedUniform(pBone, TRUE, TRUE);
		bErr = CGINTM(pBone,pExport->GetInitNodeTM(pBone, tmp));
		if (bErr) tmp.IdentityMatrix();
		Helper::SetBipedUniform(pBone, FALSE, FALSE);
	} else {
		bErr = CGINTM(pBone,pExport->GetInitNodeTM(pBone, tmp));
		if (bErr) tmp.IdentityMatrix();
	}

	if (1){//!bErr){
		Helper::ConvertMatrix(tmp,matInit);
		matOffset.invert(matInit);
		//S matMesh
//		pBone->matOffset = matMesh * Inverse(pBone->matInit);
	}

	return 1;//!bErr;
}