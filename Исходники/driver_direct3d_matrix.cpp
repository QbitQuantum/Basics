void CDriverD3D::setupViewMatrix(const CMatrix& mtx)
{
	H_AUTO_D3D(CDriverD3D_setupViewMatrix)
	// Remember the view matrix
	_UserViewMtx= mtx;
	_PZBCameraPos= CVector::Null;

	// Set the driver matrix
	D3DXMATRIX view;
	NL_D3D_MATRIX (view, mtx);

	// Pass to directx matrix basis
	swap (view._12, view._13);
	swap (view._22, view._23);
	swap (view._32, view._33);
	swap (view._42, view._43);

	setMatrix (D3DTS_VIEW, view);

	// Set the spacular matrix
	CMatrix specularTex;
	specularTex = mtx;
	specularTex.setPos(CVector(0.0f,0.0f,0.0f));
	specularTex.invert();
	NL_D3D_MATRIX (_D3DSpecularWorldTex, specularTex);

	updateMatrices ();
}