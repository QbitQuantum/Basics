void idle()
{
Timer frameTimer; frameTimer.start();
    // Timing things
    timeFrame+=1;

    double oscillationPeriod = factors.at("StimulusDuration")*TIMER_MS;

    switch (stimMotion)
    {
    case SAWTOOTH_MOTION:
        periodicValue = oscillationAmplitude*mathcommon::sawtooth(timeFrame,oscillationPeriod);
        break;
    case TRIANGLE_MOTION:
        periodicValue = oscillationAmplitude*mathcommon::trianglewave(timeFrame,oscillationPeriod);
        break;
    case SINUSOIDAL_MOTION:
        periodicValue = oscillationAmplitude*sin(3.14*timeFrame/(oscillationPeriod));
        break;
    default:
        SAWTOOTH_MOTION;
    }

    timingFile << totalTimer.getElapsedTimeInMilliSec() << " " << periodicValue << endl;

    // Simulate head translation
    // Coordinates picker
    markers[1] = Vector3d(0,0,0);
    markers[2] = Vector3d(0,10,0);
    markers[3] = Vector3d(0,0,10);

    headEyeCoords.update(markers[1],markers[2],markers[3]);

    eyeLeft = headEyeCoords.getLeftEye();
    eyeRight = headEyeCoords.getRightEye();

    Vector3d fixationPoint = (headEyeCoords.getRigidStart().getFullTransformation() * ( Vector3d(0,0,focalDistance) ) );
    // Projection of view normal on the focal plane
    Eigen::ParametrizedLine<double,3> pline = Eigen::ParametrizedLine<double,3>::Through(eyeRight,fixationPoint);
    projPoint = pline.intersection(focalPlane)*((fixationPoint - eyeRight).normalized()) + eyeRight;

    stimTransformation.matrix().setIdentity();
    stimTransformation.translation() <<0,0,focalDistance;

	Timer sleepTimer;
	sleepTimer.sleep((TIMER_MS - frameTimer.getElapsedTimeInMilliSec())/2);
}