void CCameraLook::Update(Fvector& point, Fvector& /**noise_dangle/**/)
{
	vPosition.set		(point);
	Fmatrix mR;
	mR.setHPB			(-yaw,-pitch,-roll);

	vDirection.set		(mR.k);
	vNormal.set			(mR.j);

	if (m_Flags.is(flRelativeLink)){
		parent->XFORM().transform_dir(vDirection);
		parent->XFORM().transform_dir(vNormal);
	}
	Fvector				vDir;
	collide::rq_result	R;

	float				covariance = VIEWPORT_NEAR*6.f;
	vDir.invert			(vDirection);
	g_pGameLevel->ObjectSpace.RayPick( point, vDir, dist+covariance, collide::rqtBoth, R, parent);

	float d				= psCamSlideInert*prev_d+(1.f-psCamSlideInert)*(R.range-covariance);
	prev_d = d;
	
	vPosition.mul		(vDirection,-d-VIEWPORT_NEAR);
	vPosition.add		(point);

}