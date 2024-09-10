void MindField::Update()
{
  mTime += 0.01f;

    //camera update
    Vec3f pos = mCamera.getEyePoint();
    
    Vec3f newPos = pos.lerp(mLerper, mNextCamPoint);
    mCamera.setEyePoint(newPos);
    mCamera.setCenterOfInterestPoint(Vec3f(0,0,0));
    
    mLerper = mLerper + 0.0000001* getFrameRate();
    float camBound = 8.0;
    
    float d = newPos.length();
    float maxLength = Vec3f(camBound, camBound, camBound).length();
    float t = d / maxLength;
    mBlurView = lerp(0.9,1.5,  t);
    

    if(mLerper >= 1.0)
    {
        mLerper = 0.0;
        mNextCamPoint = Vec3f(randFloat(-camBound,camBound), randFloat(-camBound,camBound), randFloat(-camBound,camBound));
    }
    
    if(pos.distance(mNextCamPoint) < 5)
    {
        mLerper = 0.0;
        mNextCamPoint = Vec3f(randFloat(-camBound, camBound), randFloat(-camBound,camBound), randFloat(-camBound,camBound));
    }
    // end camera update
    
    
    for(int i = 0; i < mNeurons.size(); i++)
    {
        Neuron* n = mNeurons[i];
        n->Update();
        int bx = floor( (n->pos.x + abs(kXLow) ) / kBXDiv);
        int by = floor( (n->pos.y + abs(kYLow) ) / kBYDiv);
        int bz = floor( (n->pos.z + abs(kZLow)) / kBZDiv);
        theMindField.mBins[bx][by][bz].push_back(i);
    }
    
    

     for( list<Axon*>::iterator p = mAxons.begin(); p != mAxons.end(); ++p )
    {
        (*p)->Update();
        
    }
    
    UpdateAxons();
    ClearBins();
    
    
    
}