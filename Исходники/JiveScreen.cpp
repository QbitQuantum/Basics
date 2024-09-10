//--------------------------------------------------------------
void JiveScreen::tweenPositionSlave(vector<ofVec2f> fP, ofVec2f posUpdate, ofVec2f positionCurr, vector< vector<int> > choreo, int step, char side, char gender, bool bdisplayIcon, bool bdisplayPrevious, bool bmoveForward, bool bcloser)
{
    // if lift
    if(choreo[step][3] == 5 && !bmoveForward)
    {
        fP.at(fP.size()-1) = positionCurr;
        posUpdate          = positionCurr;
        positionPrev       = positionCurr;
    }
    //cout << step << " - prev: " << positionPrev << " - curr: " << positionCurr << " --> update: " << posUpdate << "     out: " << fP.at(fP.size()-1) << endl;
    
    if (posUpdate != positionCurr)
    {
        int last = fP.size()-1;
        
        ofSetColor(255, 255, 255, 255);
        
        /*int distTotal = ofDist(positionPrev.x, positionPrev.y, positionCurr.x, positionCurr.y);
         int distUpdate = ofDist(fP.at(last).x, fP.at(last).y, positionCurr.x, positionCurr.y);
         //int alpha = ofMap(distUpdate, 0, distTotal, 75, 255);
         //int alpha = 255-255*distUpdate/distTotal;
         //ofSetColor(255, 255, 255, alpha);*/
        
        if(bmoveForward && gender == 'f')
        {
            Foot(fP.at(last).x, -fP.at(last).y, side, gender, config.iconSize);
        }else if(step == 0)
        {
            ofPushMatrix();
            if(gender == 'm'){
                ofRotateZ(360-rotateDegree);
                Foot(fP.at(last).x, -fP.at(last).y, side, gender, config.iconSize);
            }else{
                ofRotateZ(rotateDegree);
                Foot(fP.at(last).x, fP.at(last).y, side, gender, config.iconSize);
            }
            ofPopMatrix();
        }
        else{
            if(gender == 'm'){
                Foot(fP.at(last).x, -fP.at(last).y, side, gender, config.iconSize);
            }else{
                Foot(fP.at(last).x, fP.at(last).y, side, gender, config.iconSize);
            }
        }
        
        //alpha = 255;
        //if(distUpdate < distTotal/4) alpha = 0;
        if(bdisplayIcon) createIcon(fP, choreo, step, gender);
        //ofSetColor(255, 255, 255, 255);
    }
    else
    {
        int last = fP.size()-1;
        
        if(bmoveForward && gender == 'f')
        {
            Foot(fP.at(last).x, -fP.at(last).y, side, gender, config.iconSize);
        }
        else
        {
            // if lift
            if(choreo[step][3] == 5 && !bmoveForward)
            {
                if(bdisplayIcon) createIcon(fP, choreo, step, gender);
                
                if(!biconWasBig && newIconSize  < config.iconSize+5) newIconSize += 1;
                if(                newIconSize == config.iconSize+5) biconWasBig = true;
                if( biconWasBig && newIconSize >= config.iconSize)   newIconSize -= 1;
            }else{
                // reset
                biconWasBig = false;
                newIconSize = config.iconSize;
            }
            
            if(step == 0)
            {
                ofPushMatrix();
                if(gender == 'm'){
                    ofRotateZ(360-rotateDegree);
                    Foot(fP.at(last).x, -fP.at(last).y, side, gender, newIconSize);
                }else{
                    ofRotateZ(rotateDegree);
                    Foot(fP.at(last).x, fP.at(last).y, side, gender, newIconSize);
                }
                ofPopMatrix();
            }
            else
            {
                if(gender == 'm'){
                    Foot(fP.at(last).x, -fP.at(last).y, side, gender, newIconSize);
                }else{
                    Foot(fP.at(last).x, fP.at(last).y, side, gender, newIconSize);
                }
            }
        }
        
        //if(bdisplayIcon) createIcon(fP, choreo, step, gender);
    }
    
    if(bdisplayPrevious)
    {
        // PREVIOUS STEP --------------------------------------------
        previousStep = step-1;
        if(previousStep == -1) previousStep = 7;
        
        // get position
        ofVec2f previousStepPos;
        if(choreo[previousStep][2] == 0)
        {
            previousStepPos.x = choreo[previousStep][0]-config.distanceFeet;
            side = 'l';
        }
        else
        {
            previousStepPos.x = choreo[previousStep][0]+config.distanceFeet;
            side = 'r';
        }
        //if(previousStep == 0) previousStepPos.x = choreo[previousStep][0]-config.distanceFeet;
        previousStepPos.y = choreo[previousStep][1];
        
        // display step
        ofSetColor(255, 127);
        if(previousStep == 0)
        {
            ofPushMatrix();
            if(gender == 'm'){
                ofRotateZ(360-rotateDegree);
                Foot(previousStepPos.x, -previousStepPos.y, side, gender, config.iconSize);
            }else{
                ofRotateZ(rotateDegree);
                Foot(previousStepPos.x, previousStepPos.y, side, gender, config.iconSize);
            }
            ofPopMatrix();
        }
        else
        {
            if(gender == 'm'){
                Foot(previousStepPos.x, -previousStepPos.y, side, gender, config.iconSize);
            }else{
                Foot(previousStepPos.x, previousStepPos.y, side, gender, config.iconSize);
            }
        }

        int futureStep = previousStep+2;
        if(futureStep == 8) futureStep = 0;
        if(futureStep == 9) futureStep = 1;
        if(bdisplayIcon) createIcon(previousStepPos, choreo, futureStep, gender);
        ofSetColor(255, 255);
    }
}