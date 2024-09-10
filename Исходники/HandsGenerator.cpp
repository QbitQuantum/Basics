const bool HandsGenerator::startTracking( const kvs::Vector3f& position )
{
    if ( !m_is_created )
    {
        kvsMessageError( "HandsGenerator is not created yet." );
        return( false );
    }

    XnPoint3D pos;
    pos.X = position.x();
    pos.Y = position.y();
    pos.Z = position.z();

    XnStatus status = m_generator.StartTracking( pos );
    if ( status != XN_STATUS_OK )
    {
        kvsMessageError( "%s error: <%s>.",
            xnGetStatusName( status ),
            xnGetStatusString( status ) );
        return( false );
    }

    return( true );
}