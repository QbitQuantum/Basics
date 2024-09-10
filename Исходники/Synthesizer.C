// ---------------------------------------------------------------------------
//  synthesize
// ---------------------------------------------------------------------------
//! Synthesize a bandwidth-enhanced sinusoidal Partial. Zero-amplitude
//! Breakpoints are inserted at either end of the Partial to reduce
//! turn-on and turn-off artifacts, as described above. The synthesizer
//! will resize the buffer as necessary to accommodate all the samples,
//! including the fade out. Previous contents of the buffer are not
//! overwritten. Partials with start times earlier than the Partial fade
//! time will have shorter onset fades. Partials are not rendered at
//! frequencies above the half-sample rate. 
//!
//! \param  p The Partial to synthesize.
//! \return Nothing.
//! \pre    The partial must have non-negative start time.
//! \post   This Synthesizer's sample buffer (vector) has been 
//!         resized to accommodate the entire duration of the 
//!         Partial, p, including fade out at the end.
//! \throw  InvalidPartial if the Partial has negative start time.
//  
void
Synthesizer::synthesize( Partial p ) 
{
    if ( p.numBreakpoints() == 0 )
    {
        debugger << "Synthesizer ignoring a partial that contains no Breakpoints" << endl;
        return;
    }
    
    if ( p.startTime() < 0 )
    {
        Throw( InvalidPartial, "Tried to synthesize a Partial having start time less than 0." );
    }

    debugger << "synthesizing Partial from " << p.startTime() * m_srateHz 
             << " to " << p.endTime() * m_srateHz << " starting phase "
             << p.initialPhase() << " starting frequency " 
             << p.first().frequency() << endl;
             
    //  better to compute this only once:
    const double OneOverSrate = 1. / m_srateHz;
    
             
    //  use a Resampler to quantize the Breakpoint times and 
    //  correct the phases:
    Resampler quantizer( OneOverSrate );
    quantizer.setPhaseCorrect( true );
    quantizer.quantize( p );
    

    //  resize the sample buffer if necessary:
    typedef unsigned long index_type;
    index_type endSamp = index_type( ( p.endTime() + m_fadeTimeSec ) * m_srateHz );
    if ( endSamp+1 > m_sampleBuffer->size() )
    {
        //  pad by one sample:
        m_sampleBuffer->resize( endSamp+1 );
    }
    
    //  compute the starting time for synthesis of this Partial,
    //  m_fadeTimeSec before the Partial's startTime, but not before 0:
    double itime = ( m_fadeTimeSec < p.startTime() ) ? ( p.startTime() - m_fadeTimeSec ) : 0.;
    index_type currentSamp = index_type( (itime * m_srateHz) + 0.5 );   //  cheap rounding
    
    //  reset the oscillator:
    //  all that really needs to happen here is setting the frequency
    //  correctly, the phase will be reset again in the loop over 
    //  Breakpoints below, and the amp and bw can start at 0.
    m_osc.resetEnvelopes( BreakpointUtils::makeNullBefore( p.first(), p.startTime() - itime ), m_srateHz );

    //  cache the previous frequency (in Hz) so that it
    //  can be used to reset the phase when necessary
    //  in the sample computation loop below (this saves
    //  having to recompute from the oscillator's radian
    //  frequency):
    double prevFrequency = p.first().frequency();   
    
    //  synthesize linear-frequency segments until 
    //  there aren't any more Breakpoints to make segments:
    double * bufferBegin = &( m_sampleBuffer->front() );
    for ( Partial::const_iterator it = p.begin(); it != p.end(); ++it )
    {
        index_type tgtSamp = index_type( (it.time() * m_srateHz) + 0.5 );   //  cheap rounding
        Assert( tgtSamp >= currentSamp );
        
        //  if the current oscillator amplitude is
        //  zero, and the target Breakpoint amplitude
        //  is not, reset the oscillator phase so that
        //  it matches exactly the target Breakpoint 
        //  phase at tgtSamp:
        if ( m_osc.amplitude() == 0. )
        {
            //  recompute the phase so that it is correct
            //  at the target Breakpoint (need to do this
            //  because the null Breakpoint phase was computed
            //  from an interval in seconds, not samples, so
            //  it might be inaccurate):
            //
            //  double favg = 0.5 * ( prevFrequency + it.breakpoint().frequency() );
            //  double dphase = 2 * Pi * favg * ( tgtSamp - currentSamp ) / m_srateHz;
            //
            double dphase = Pi * ( prevFrequency + it.breakpoint().frequency() ) 
                               * ( tgtSamp - currentSamp ) * OneOverSrate;
            m_osc.setPhase( it.breakpoint().phase() - dphase );
        }

        m_osc.oscillate( bufferBegin + currentSamp, bufferBegin + tgtSamp,
                         it.breakpoint(), m_srateHz );
        
        currentSamp = tgtSamp;
        
        //  remember the frequency, may need it to reset the 
        //  phase if a Null Breakpoint is encountered:
        prevFrequency = it.breakpoint().frequency();
    }

    //  render a fade out segment:  
    m_osc.oscillate( bufferBegin + currentSamp, bufferBegin + endSamp,
                     BreakpointUtils::makeNullAfter( p.last(), m_fadeTimeSec ), m_srateHz );
    
}