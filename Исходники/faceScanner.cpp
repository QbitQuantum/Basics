void FaceScanner::update()
{
    m_grabber.update();
    
    if(m_grabber.isFrameNew())
    {
        if (m_shouldTrack)
        {
            m_tracker.update(toCv(m_grabber));
            
            //----If we've found a face, we store its intrinsics and begin our scanning procedure
            if (m_tracker.getFound() &&                                                                 //Have we found a face?
                ofGetElapsedTimef() > 2.0f &&                                                           //Has it been at least 2 seconds?
                m_tracker.getImageFeature(ofxFaceTracker::FACE_OUTLINE).getArea() > MIN_FACE_AREA)      //If we've found a face, is it reasonably large?
            {
                ofLogNotice("Face Scanner") << "Found a face.";
                
                //----The FBOs are cleared IFF the last sequence drawn was the particle system (denoted by the boolean m_shouldClearAmbient)
                if (!m_shouldClearAmbient) m_inkRenderer->clear();
                
                m_inkRenderer->setDrawMode(InkRenderer::FOLLOWERS);
                convertColor(m_grabber, m_thresh, CV_RGB2GRAY);
                
                m_faceOutline =         m_tracker.getImageFeature(ofxFaceTracker::FACE_OUTLINE);
                m_faceCenter =          m_faceOutline.getCentroid2D();
                m_faceArea =            m_faceOutline.getArea();       //This is a hack: something is wrong with the sign of the value returned by getArea()
                m_faceBoundingBox =     m_faceOutline.getBoundingBox();
                
                m_shouldTrack =         false;
                m_drawFrameStart =      ofGetElapsedTimef();                //When did this scan start?
                
                scan(200, 10);                                               //Start at a threshold value of 200, and decrement by 5 for each iteration
            }
            else
            {
                //----If we don't see a face and it's been m_ambientTimeout seconds, enter ambient mode
                if ((ofGetElapsedTimef() - m_ambientFrameStart) >= m_ambientTimeout) {
                    
                    //----We only want to do these operations once, otherwise the FBOs will clear every frame, and the particle system will never be drawn
                    if (m_shouldClearAmbient)
                    {
                        ofLogNotice("Face Scanner") << "Entering ambient mode.";
                        
                        //----We tell the InkRenderer to draw particles after clearing the FBOs and resetting the "draw counter"
                        m_inkRenderer->setDrawMode(InkRenderer::PARTICLES);
                        m_inkRenderer->clear();
                        m_shouldClearAmbient = false;
                    }
                }
            }
        }
        else if ((ofGetElapsedTimef() - m_drawFrameStart) >= m_drawTimeout)
        {
            //----If we shouldn't be tracking, that means we've already found a face, so begin the countdown
            ofLogNotice("Face Scanner") << "Starting a new scan.";
            
            //----After this point, we might not see another face, so we record the current time and ready the InkRenderer for a particle simulation
            m_ambientFrameStart =   ofGetElapsedTimef();
            m_shouldClearAmbient =  true;
            ofSaveScreen("screenshots/image_" + ofGetTimestampString() + ".png");
            
            reset();
        }
    }
}