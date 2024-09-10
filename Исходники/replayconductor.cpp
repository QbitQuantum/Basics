void
ReplayConductor::handleEvents()
{
    IceUtil::Mutex::Lock lock(mutex_);

    // Pop all the events off the queue and deal with them.
    while ( !eventQueue_.empty() )
    {
        Event e = eventQueue_.front();
        eventQueue_.pop();

        switch ( e.type() )
        {
        case SetReplayRate:
            handleSetReplayRate(e.replayRate());
            break;
        case Start:
            handleStart();
            break;
        case Pause:
            handlePause();
            break;
        case StepForward:
            handleStepForward();
            break;
        case StepBackward:
            handleStepBackward();
            break;
        case FastForward:
            handleFastForward(e.time());
            break;
        case FastForwardToEnd:
            handleFastForwardToEnd();
            break;
        case Rewind:
            handleRewind(e.time());
            break;
        case RewindToStartAndStop:
            handleRewindToStartAndStop();
            break;
        default:
            cout << "ERROR(replayconductor.cpp): Don't know how to handle event: " << toString(e) << endl;
        }
    }
}