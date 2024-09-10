void redEyeApp::drawSpectrum(bool fill) {
    if(!mFftLeft) {
        return;
    }
    float *fftBuffer= mFftLeft.get();
    float w= getWindowWidth();
    float a= getWindowHeight()*0.01f;    //spectrum scale
    uint32_t fftSize= mBufferSize/2;
    PolyLine<Vec2f>	line;
    for(uint32_t i= 0; i<fftSize; i++) {
        float x= (i/(float)(fftSize-1))*w-(w*0.5f);
        float y= fftBuffer[i]*a;
        line.push_back(Vec2f(x, 0.0f-y));
        if(fill) {
            line.push_back(Vec2f(x, y));
        }
    }
    gl::draw(line);
}