void keyPressed()
{   if ( trialMode == PROBEMODE )
    {   if ( trialNumber==0)
        {   responseFile << setw(6) << left <<
                         "TrialNumber DeltaSlant StillPlaneSlant PlanesCentersYDistance Onset WhichPlaneUp StairState StairAscending EyeCalx EyeCaly EyeCalz StimFrames StimDuration ResponseTime Answer OverallTilt" << endl;
        }
        responseFile << fixed <<
                     trialNumber << " " <<
                     factors.at("DeltaSlant") << " " <<
                     factors.at("StillPlaneSlant") << " " <<
                     factors.at("PlanesCentersYDistance") << " " << 
                     factors.at("Onset") << " " <<
                     whichPlaneDrawUp << " " << 
					 alphaMultiplier << " " << 
					 currentStaircaseIsAscending << " " << 
                     eyeCalibration.transpose() << " " <<
                     stimulusFrames << " " <<
                     stimulusTime << " " <<
                     responseTimer.getElapsedTimeInMilliSec() << " " <<
                     answer << " " <<
					 overallTilt << " " << endl;

        responseTimer.start();
        stimulusDuration.start();

        for (int i=0; i<2; i++)
        {
            redDotsPlane[i].compute();
            stimDrawer[i].initList(&redDotsPlane[i]);
        }
        isReading=true;
        // Winds down the file until probemode isn't finished
        while ( trialMode == PROBEMODE  || trialMode == CALIBRATIONMODE )
        {   if ( readline(inputStream, trialNumber,  headCalibration,  trialMode, pointMatrix ) )
            {   exit(0);
            }
        }
        beepOk();
    }
}