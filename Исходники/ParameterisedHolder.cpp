void ParameterisedHolder<B>::nonNetworkedConnections( const MPlug &plug, MPlugArray &connectionsFromPlug, MPlugArray &connectionsToPlug ) const
{
    MPlugArray from;
    MPlugArray to;

    // the MPlug.connectedTo() method is documented as always returning networked plugs.
    plug.connectedTo( from, false, true );
    plug.connectedTo( to, true, false );

    connectionsFromPlug.clear();
    connectionsFromPlug.setLength( from.length() );
    connectionsToPlug.clear();
    connectionsToPlug.setLength( to.length() );

    for( unsigned i=0; i<from.length(); i++ )
    {
        // the MPlug( node, attribute ) constructor is documented as always returning non-networked plugs.
        connectionsFromPlug.set( MPlug( from[i].node(), from[i].attribute() ), i );
    }

    for( unsigned i=0; i<to.length(); i++ )
    {
        connectionsToPlug.set( MPlug( to[i].node(), to[i].attribute() ), i );
    }
}