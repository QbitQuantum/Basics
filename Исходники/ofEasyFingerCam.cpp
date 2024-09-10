//----------------------------------------
ofEasyFingerCam::ofEasyFingerCam()
{
    selectedPlane = new AxisPlane();
    drag = 0.1f;
    zoomSpeed = 2.0f;
    bMouseInputEnabled = false;
    bFingerInputEnabled = false;
    mousePosViewPrev.set(0, 0);
    lastFrame = 0;
    bDistanceSet = false;
    lastDistance = 0;
    distanceScaleVelocity = 0;
    fingers = std::vector<Finger *>();
    target.setPosition(0, 0, 0);
    zooming = true;
    reset();
    setParent(target);
    prevDistance = 0;
    ofVec3f center = ofVec3f(0.0f, 0.0f, 0.0f);
    ofVec3f normal = ofVec3f(0.0f, 1.0f, 0.0f).normalize();
    ofVec2f scale = ofVec2f(1.0f, 1.0f);
    enableMouseInput();
    enableFingerInput();
}