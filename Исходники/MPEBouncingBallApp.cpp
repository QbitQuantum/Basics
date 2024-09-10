void MPEBouncingBallApp::mpeReset()
{
    console() << "RESETTING\n";

    // Set the random seed to a known value so all of the clients are using the same rand values.
    mRand.seed(1);

    // Clear out the previous state
    mServerFramesProcessed = 0;
    mBalls.clear();

    // Add the first ball
    ivec2 sizeMaster = mClient->getMasterSize();
    addBallAtPosition(vec2(mRand.nextFloat(sizeMaster.x), mRand.nextFloat(sizeMaster.y)));
    
    if (mClient->isAsynchronousClient())
    {
        send3DSettings();
    }
}