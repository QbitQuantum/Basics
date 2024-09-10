// ---------------------------------------------------------------------------
//    harmonify
// ---------------------------------------------------------------------------
//! Apply the reference envelope to a Partial.
//!
//! \pre    The Partial p must be labeled with its harmonic number.
//
void Harmonifier::harmonify( Partial & p ) const
{
    //    compute absolute magnitude thresholds:
    static const double FadeRangeDB = 10;
    const double BeginFade = std::pow( 10., 0.05 * (_freqFixThresholdDb+FadeRangeDB) );
    const double Threshold = std::pow( 10., 0.05 * _freqFixThresholdDb );
    const double OneOverFadeSpan = 1. / ( BeginFade - Threshold );

    double fscale = (double)p.label() / _refPartial.label();
    
    for ( Partial::iterator it = p.begin(); it != p.end(); ++it )
    {
        Breakpoint & bp = it.breakpoint();            
                
        if ( bp.amplitude() < BeginFade )
        {
            //  alpha is the harmonic frequency weighting:
            //  when alpha is 1, the harmonic frequency is used,
            //  when alpha is 0, the breakpoint frequency is
            //  unmodified.
            double alpha = 
                std::min( ( BeginFade - bp.amplitude() ) * OneOverFadeSpan, 1. );
                
            //  alpha is scaled by the weigthing envelope
            alpha *= _weight->valueAt( it.time() );
            
            double fRef = _refPartial.frequencyAt( it.time() );
            
            bp.setFrequency( ( alpha * ( fRef * fscale ) ) + 
                             ( (1 - alpha) * bp.frequency() ) );
        }

    }
}