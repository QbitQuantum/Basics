void WandCameraController::handleEvent(const Event& evt)
{
    if(!isEnabled()) return;
    
    int uid = getCamera()->getTrackerUserId();

    // Process this event if the event is a wand AND
    // - the camera has a used id that is the same as this event user id OR
    // - the controller wand id is the same ad the event source id OR
    // - the controller wand id is -1 (any wand)
    if(evt.getServiceType() == Service::Wand && 
        (evt.getUserId() == uid ||
         (uid == -1 &&
         (myWandSourceId == evt.getSourceId() || 
         myWandSourceId == -1 ))))
    {
        //ofmsg("Wand %1%", %evt.getUserId());
        if(evt.isFlagSet(myOverrideButton))
        {
            myOverride = true;
            return;
        }
        else myOverride = false;
        
        float x = evt.getExtraDataFloat(0);
        float y = evt.getExtraDataFloat(1);
        
        // Thresholds
        if(x < 0.1f && x > -0.1f) x = 0;
        if(y < 0.1f && y > -0.1f) y = 0;
        
        myYaw = -x * myRotateSpeed;

        // Move forward using wand analog control
        Quaternion orientation = evt.getOrientation() * getCamera()->getCanvasOrientation();
        mySpeed = orientation * Vector3f(0, 0, y / 2) * 
            CameraController::mySpeed;
        
        if(evt.isFlagSet(myNavigateButton)) 
        {
            if(myNavigating == false)
            {
                myLastPointerPosition = evt.getPosition();
                myAxisCorrection = getCamera()->getDerivedOrientation();
                Quaternion o = myAxisCorrection * evt.getOrientation();
                myLastPointerOrientation = o.inverse() * getCamera()->getOrientation();
            }
            myNavigating = true;
        }
        else
        {
            myNavigating = false;
        }
        
        if(myNavigating)
        {
            // Move in any direction using wand position tracking.
            Vector3f dv = (evt.getPosition() - myLastPointerPosition) *
                CameraController::mySpeed * 4;
            mySpeed += getCamera()->getCanvasOrientation() * dv;

            if(myFreeFlyEnabled)
            {
                Quaternion o = myAxisCorrection * evt.getOrientation();
                myTorque = o * myLastPointerOrientation;
            }
        }
    }
}