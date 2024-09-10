void CinderProjectionTestApp::update()
{
	mLookEye.normalize();
	mLookEye *= abs(mLookDistance);
	mLookCam.lookAt(mLookEye, mLookCenter);
	//mLookCam.setOrientation( mArcball.getQuat() );
	mSweetCam.lookAt(mSweetEye, mSweetCenter);
	mProjCam.lookAt(mProjEye, mProjCenter);
	
	mFPS = getAverageFps();
}