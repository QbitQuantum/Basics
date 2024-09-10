void keyPressed()
{
    if ( trialMode == PROBEMODE )
    {
        if ( trialNumber==0)
        {   responseFile << setw(6) << left <<
                         "TrialNumber" << "Tilt Slant Rotation RotationSpeed FollowingSpeed Onset EyeCal.x EyeCal.y EyeCal.z StimFrames ProbeAngle" << endl;
        }
        responseFile << setw(6) << left <<
                     trialNumber << " " <<
                     factors["Tilt"] << " "  <<
                     factors["Slant"] << " " <<
                     factors["Rotation"] << " " <<
                     factors["RotationSpeed"] << " " <<
                     factors["FollowingSpeed"] << " " <<
                     factors["Onset"] << " " <<
                     eyeCalibration.transpose() << " " <<
					 stimulusFrames << " " <<
                     probeAngle << endl;

        double possibleAngles[]= {0,90,180,270};
        probeStartingAngle=possibleAngles[rand()%4];
        redDotsPlane.compute();
        
		stimDrawer.initList(&redDotsPlane);

        isReading=true;
        // Winds down the file until probemode isn't finished
        while ( trialMode == PROBEMODE  || trialMode == CALIBRATIONMODE )
        {   if ( readline(inputStream, trialNumber,  headCalibration,  trialMode, pointMatrix ) )
            {
                cleanup();
                exit(0);
            }
        }
        
    #ifdef _WIN32
    beepOk();
    #endif
	}
}