//-------------------------------------------------------------------------------
// @ IvQuat::Set()
//-------------------------------------------------------------------------------
// Set quaternion based on start and end vectors
//-------------------------------------------------------------------------------
void
IvQuat::Set( const IvVector3& from, const IvVector3& to )
{
    // Ensure that our vectors are unit
    ASSERT( from.IsUnit() && to.IsUnit() );

    // get axis of rotation
    IvVector3 axis = from.Cross( to );
    // get cos of angle between vectors
    float costheta = from.Dot( to );

    // if vectors are 180 degrees apart
    if ( costheta <= -1.0f )
    {
        // find orthogonal vector
        IvVector3 orthoVector;
        orthoVector.Normalize();

        w = 0.0f;
        x = orthoVector.x;
        y = orthoVector.y;
        z = orthoVector.z;

        return;
    }

    // use trig identities to get the values we want
    float factor = IvSqrt( 2.0f*(1.0f + costheta) );
    float scaleFactor = 1.0f/factor;

    // set values
    w = 0.5f*factor;
    x = scaleFactor*axis.x;
    y = scaleFactor*axis.y;
    z = scaleFactor*axis.z;

}   // End of IvQuat::Set()