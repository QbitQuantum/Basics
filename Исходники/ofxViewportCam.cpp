//----------------------------------------
void ofxViewportCam::frameBoundingBox(const ofVec3f &minCorner,
                                     const ofVec3f &maxCorner)
{
    ofVec3f center((minCorner + maxCorner) * 0.5f);
    setTargetPosition(center);
    this->distance = minCorner.distance(maxCorner);
    
    setPosition(target.getGlobalPosition());
    dolly(this->distance);
}