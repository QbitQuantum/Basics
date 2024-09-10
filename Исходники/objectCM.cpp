bool ObjectCM::sendSync( const MasterCMCommand& command )
{
    lunchbox::ScopedFastWrite mutex( _lock );
    if( !_object )
    {
        LBWARN << "Sync from detached object requested" << std::endl;
        return false;
    }

    const uint128_t& maxCachedVersion = command.getMaxCachedVersion();
    const bool useCache =
        command.useCache() &&
        command.getMasterInstanceID() == _object->getInstanceID() &&
        maxCachedVersion == getVersion();

    if( !useCache )
    {
        ObjectInstanceDataOStream os( this );
        os.enableSync( getVersion(), command );
        _object->getInstanceData( os );
        os.disable();
    }
    NodePtr node = command.getNode();
    node->send( CMD_NODE_SYNC_OBJECT_REPLY, useCache /*preferMulticast*/ )
        << node->getNodeID() << command.getObjectID() << command.getRequestID()
        << true << command.useCache() << useCache;
    return true;
}