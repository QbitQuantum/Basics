//---------------------------------------------------------------------------
float ofxKinect::getAccelRoll(){
	return ofRadToDeg(asin(getMksAccel().x/OFX_KINECT_GRAVITY));
}