void CVehicleMovementAerodynamic::UpdateWing(SWing *_pWing,float _fAngle,float _fDeltaTime)
{
	Matrix34 matWing = m_pEntity->GetWorldTM() * Matrix33::CreateRotationXYZ(Ang3(DEG2RAD(_pWing->fAngleX),
																																								DEG2RAD(_pWing->fAngleY),
																																								DEG2RAD(_pWing->fAngleZ))).GetInverted();

	Vec3 vRight	= matWing.GetColumn(0);
	Vec3 vLook	= matWing.GetColumn(1);
	Vec3 vUp		= matWing.GetColumn(2);

	pe_status_dynamics StatusDynamics;
	GetPhysics()->GetStatus(&StatusDynamics);

	// v(relativepoint) = v + w^(relativepoint-center)
	Vec3 vVelocity = StatusDynamics.v + StatusDynamics.w.Cross(m_pEntity->GetWorldTM().TransformVector(_pWing->vPos));
	Vec3 vVelocityNormalized = vVelocity.GetNormalizedSafe(vLook);

	// TODO:

	float fAngleOfAttack = RAD2DEG(asin(vRight.Dot(vVelocityNormalized.Cross(vLook))));

	DumpText("AoA=%f",fAngleOfAttack);

	fAngleOfAttack += _fAngle;

	float Cl = GetCoefficient(_pWing->pLiftPointsMap,fAngleOfAttack) * _pWing->fCl;
	float Cd = GetCoefficient(_pWing->pDragPointsMap,fAngleOfAttack) * _pWing->fCd;

	Vec3 vVelocityNormal = vRight.Cross(vVelocityNormalized).GetNormalized();

	float fVelocitySquared = vVelocity.len2();

	const float c_fDynamicPressure = 1.293f;

	float fLift = 0.5f * c_fDynamicPressure * _pWing->fSurface * Cl * fVelocitySquared * _fDeltaTime;
	float fDrag = 0.5f * c_fDynamicPressure * _pWing->fSurface * Cd * fVelocitySquared * _fDeltaTime;

	Vec3 vLiftImpulse = +fLift * vVelocityNormal;
	Vec3 vDragImpulse = -fDrag * vVelocityNormalized;

	AddForce(&vLiftImpulse,&_pWing->vPos,ColorF(0,1,0,1));
	AddForce(&vDragImpulse,&_pWing->vPos,ColorF(1,0,1,1));
}