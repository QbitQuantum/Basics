const kvs::Vector3f DepthGenerator::realPosition( const kvs::Vector3f& pos )
{
    if ( !m_is_created )
    {
        kvsMessageError( "DepthGenerator is not created yet." );
        return( pos );
    }

    XnPoint3D proj;
    XnPoint3D real;
    proj.X = pos.x();
    proj.Y = pos.y();
    proj.Z = pos.z();

    XnStatus status = m_generator.ConvertProjectiveToRealWorld( 1, &proj, &real );
    if ( status != XN_STATUS_OK )
    {
        kvsMessageError( "%s error: <%s>.",
            xnGetStatusName( status ),
            xnGetStatusString( status ) );
        return( pos );
    }

    return( kvs::Vector3f( real.X, real.Y, real.Z ) );
}