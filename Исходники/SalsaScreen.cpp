//--------------------------------------------------------------
void SalsaScreen::getChoreoPosition(int step, char gender, bool displayPrevious, vector< vector<int> > choreo, bool bdisplayIcon)
{
    // CURRENT POSITION ----------------------------------------
    char side;
    if(choreo[step][2] == 0)
    {
        positionCurr.x = choreo[step][0]-config.distanceFeet;
        side = 'l';
    }
    else
    {
        positionCurr.x = choreo[step][0]+config.distanceFeet;
        side = 'r';
    }
    positionCurr.y = choreo[step][1];
    
    // DISPLAY STEP --------------------------------------------
    // set color
    ofSetColor(255);
    if(displayPrevious) ofSetColor(255, 127);
    
    Foot(positionCurr.x, positionCurr.y, side, gender, config.iconSize);
    
    int nextStep = step+2;
    if(nextStep == 6) nextStep = 0;
    if(nextStep == 7) nextStep = 1;
    
    if(bdisplayIcon) createIcon(positionCurr, choreo, nextStep, gender);
    
    // PREVIOUS STEP -------------------------------------------
    if(displayPrevious)
    {
        previousStep = step-1;
        if(previousStep == -1) previousStep = 5;
        getChoreoPosition(previousStep, gender, false, choreo, bdisplayIcon);
    }
}