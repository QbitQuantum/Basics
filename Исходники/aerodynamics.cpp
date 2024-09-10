//! Compute shock deflection angle.
double computeShockDeflectionAngle( double shockAngle, double machNumber,
                                    double ratioOfSpecificHeats )
{
    // Declare local variables.
    double tangentOfDeflectionAngle_;

    // Calculate tangent of deflection angle.
    tangentOfDeflectionAngle_ = 2.0 * ( pow( machNumber * sin( shockAngle ), 2.0 ) - 1.0 )
            / ( tan( shockAngle ) * ( pow( machNumber, 2.0 )
                                      * ( ratioOfSpecificHeats
                                          + cos( 2.0 * shockAngle ) ) + 2.0 ) );

    // Return deflection angle.
    return atan( tangentOfDeflectionAngle_ );
}