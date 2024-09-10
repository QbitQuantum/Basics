/**
 * @brief advanceTrial: This function to the next trial
 */
void advanceTrial()
{
    fingersTimer.start(); // Here we change trial mode

    if (trialMode == HANDONSTARTMODE )
    {
        // Wait to show the stimulus that the fingers points are projected in the screen
        trialMode = STIMULUSMODE;
    }
    else // trialMode == STIMULUSMODE
    {
		trialMode = HANDONSTARTMODE;
		paintGL();
		beepTrial();
		double oldDistance = factors.getCurrent().at("Distances");
        // Reinsert the trial if too much occluded frames
		double maxInvisibleFramesPercent = util::str2num<double>(parameters.find("MaxPercentOccludedFrames"))/100.0;
		if ( (invisibleIndexFrames / ((double)drawingTrialFrame) > maxInvisibleFramesPercent ) ||
			(invisibleThumbFrames / ((double)drawingTrialFrame) > maxInvisibleFramesPercent )||
			(invisibleWristFrames / ((double)drawingTrialFrame) > maxInvisibleFramesPercent ) )
		{
			map<string,double> currentFactorsList = factors.getCurrent();
            beepBad();
            cerr << "Reinserted current trial (InvIndex,InvThumb,drawingTrialFrame,totTrialFrame)" << invisibleIndexFrames << " " << invisibleThumbFrames << " " << drawingTrialFrame << " " << trialFrame << endl;
            factors.reinsert(currentFactorsList);
		}
		if (factors.isEmpty())
        {
            beepLong();
            beepLong();
            beepLong();
            plato_stop();
			exit(0);
        }
        invisibleIndexFrames = invisibleThumbFrames = invisibleWristFrames = trialFrame = drawingTrialFrame = 0;
        totalTrialNumber++;
		factors.next();
		
		if (oldDistance == factors.getCurrent().at("Distances"))
		{
			Timer sleepTimer; sleepTimer.sleep(1000);
		}
		
		double marker5z = markers.at(5).p.z();
		generateSphereStimulus( factors.getCurrent().at("StimulusRadius") );
        initProjectionScreen(factors.getCurrent().at("Distances"));
        moveStimulusObject(visualStimCenter,3500);
    }
}