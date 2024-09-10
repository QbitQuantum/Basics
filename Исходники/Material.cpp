// ***************************************************************************
void					CMaterial::decompUserTexMat(uint stage, float &uTrans, float &vTrans, float &wRot, float &uScale, float &vScale)
{
	nlassert(stage < IDRV_MAT_MAXTEXTURES);
	nlassert(isUserTexMatEnabled(stage)); // must activate animated texture matrix for this stage
	CMatrix convMat; // exported v are already inverted (todo: optim this...)
	convMat.setRot(CVector::I, -CVector::J, CVector::K);
	convMat.setPos(CVector::J);

	const NLMISC::CMatrix texMat = convMat * _TexUserMat->TexMat[stage] * convMat;
	/// find the rotation around w
	NLMISC::CVector i = texMat.getI();
	NLMISC::CVector j = texMat.getJ();
	uScale = sqrtf(i.x * i.x + j.x * j.x);
	vScale = sqrtf(i.y * i.y + j.y * j.y);
	//
	i.normalize();
	//
	float angle = acosf(i.x / i.norm());
	if (i.y < 0)
	{
		angle = 2.f * (float) NLMISC::Pi - angle;
	}
	wRot = angle;

	// compute position
	CMatrix InvSR;
	InvSR.setRot(texMat.getI(), texMat.getJ(), texMat.getK());
	InvSR.invert();
	CVector half(0.5f, 0.5f, 0.f);
	CVector offset = half + InvSR * (texMat.getPos() -half);
	uTrans = - offset.x;
	vTrans = - offset.y;
}