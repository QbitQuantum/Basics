void Cubes::Update()
{
    cubeTimer += 0.1f;

    Vec3f pos = cubesCamera.getEyePoint();
    
    Vec3f newPos = pos.lerp(mLerper, mNextCamPoint);
    cubesCamera.setEyePoint(newPos);
    cubesCamera.setCenterOfInterestPoint(Vec3f(0,0,0));
    
    mLerper = mLerper + 0.0000001* getFrameRate();
    if(mLerper >= 1.0)
    {
        mLerper = 0.0;
        mNextCamPoint = Vec3f(randFloat(-10,10), randFloat(-10,10), randFloat(-10,10));
    }
    
    if(pos.distance(mNextCamPoint) < 5)
    {
        mLerper = 0.0;
        mNextCamPoint = Vec3f(randFloat(-10,10), randFloat(-10,10), randFloat(-10,10));
    }
    
}