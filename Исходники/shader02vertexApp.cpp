void shader02vertexApp::drawWaveform(bool fill) {
    if(!mPcmBuffer) {
        return;
    }
    glPushMatrix();
    gl::translate(getWindowCenter());
    float w= getWindowWidth();
    float a= getWindowHeight()*0.25f;    //wave amplitude
    PolyLine<Vec2f>	line;
    for(uint32_t i= 0; i<mBufferSize; i++) {
        float x= (i/(float)(mBufferSize-1))*w-(w*0.5f);
        float y= mBufferLeft->mData[i]*a;
        line.push_back(Vec2f(x, y));
        if(fill) {
            line.push_back(Vec2f(x, 0.0f-y));
        }
    }
    gl::draw(line);
    glPopMatrix();
}