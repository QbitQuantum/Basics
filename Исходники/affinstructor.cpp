void StaticLineInstructor::AgainstTheWind::onUpdateOrder(float dt)
{
    // base behaviour
    Notification::onUpdateOrder( dt );

    // check dot product
    if( isLocked() )
    {
        Vector3f jumperAt = getJumper()->getClump()->getFrame()->getAt();
        jumperAt[1] = 0;
        jumperAt.normalize();
        float dotProduct = Vector3f::dot( jumperAt, _wind );
        float vel = getJumper()->getVel().length() * 0.01f;
        if( dotProduct > 0.77 )
        {
            setMessage( wstrformat( Gameplay::iLanguage->getUnicodeString(278), _orderText.c_str(), vel ).c_str() );
        }
        else if( dotProduct > -0.77 )
        {
            setMessage( wstrformat( Gameplay::iLanguage->getUnicodeString(277), _orderText.c_str(), vel ).c_str() );
        }
        else
        {
            setMessage( wstrformat( Gameplay::iLanguage->getUnicodeString(271), _orderText.c_str(), vel ).c_str() );
        }

        // end of order - by altitude
        Vector3f jumperPos = getJumper()->getClump()->getFrame()->getPos();
        if( jumperPos[1] < _orderAltitude ) setLock( false );
    }
}