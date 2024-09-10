//---------------------------------------------------------------------------
void Plots::onCurrentFrameChanged()
{
    // position of the current frame has changed 

    if ( isZoomed() )
    {
        const int n = m_frameInterval.count();

        const int from = qBound( 0, framePos() - n / 2, numFrames() - n );
        const int to = from + n - 1;

        if ( from != m_frameInterval.from )
        {
            setVisibleFrames( from, to );
            replotAll();
        }
    }

    setCursorPos( framePos() );
}