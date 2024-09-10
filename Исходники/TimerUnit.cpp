bool TimerUnit::killTimer( QString & name )
{
    //qDebug()<<"TimerUnit::killTimer() name="<<name;
    typedef list<TTimer *>::const_iterator I;
    for( I it = mTimerRootNodeList.begin(); it != mTimerRootNodeList.end(); it++)
    {
        TTimer * pChild = *it;
        if( pChild->getName() == name )
        {
            // only temporary timers can be killed
            if( ! pChild->isTempTimer() ) return false;
            pChild->killTimer();
            markCleanup( pChild );
            return true;
        }
    }
    return false;
}