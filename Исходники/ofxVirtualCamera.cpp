#include "ofxVirtualCamera.h"

const float fovWidth = 1.0144686707507438;
const float fovHeight = 0.78980943449644714;
const float XtoZ = tanf(fovWidth/2)*2;
const float YtoZ = tanf(fovHeight/2)*2;
const unsigned int camWidth = 640;
const unsigned int camHeight = 480;

ofxVec3f ConvertProjectiveToRealWorld(float x, float y, float z) {
	return ofxVec3f(-(x/camWidth-.5f) * z * XtoZ, // -x for front-mounted cameras
									(y/camHeight-.5f) * z * YtoZ,
									z);
}

ofxVirtualCamera::ofxVirtualCamera() :
newFrame(false),
maxLen(1),
stepSize(1),
nearClipping(-1024),
farClipping(1024),
orthoScale(1),
position(ofxVec3f(0, 0, 0)),
rotation(ofxVec3f(0, 0, 0)) {
}

ofxVirtualCamera::~ofxVirtualCamera() {
	kinect.close();
}

void ofxVirtualCamera::setup() {