void CCameraManager::Dump()
{
	Fmatrix mInvCamera;
	Fvector _R,_U,_T,_P;
	
	mInvCamera.invert(Device.mView);
	_R.set( mInvCamera._11, mInvCamera._12, mInvCamera._13 );
	_U.set( mInvCamera._21, mInvCamera._22, mInvCamera._23 );
	_T.set( mInvCamera._31, mInvCamera._32, mInvCamera._33 );
	_P.set( mInvCamera._41, mInvCamera._42, mInvCamera._43 );
	Log("CCameraManager::Dump::vPosition  = ",_P);
	Log("CCameraManager::Dump::vDirection = ",_T);
	Log("CCameraManager::Dump::vNormal    = ",_U);
	Log("CCameraManager::Dump::vRight     = ",_R);
}