bool FullMasterCM::sendSync( const MasterCMCommand& command )
{
    //const uint128_t& version = command.getRequestedVersion();
    const uint128_t& maxCachedVersion = command.getMaxCachedVersion();
    const bool useCache =
        command.useCache() &&
        command.getMasterInstanceID() == _object->getInstanceID() &&
        maxCachedVersion == _version;

    if( !useCache )
    {
        Mutex mutex( _slaves );
        InstanceData* instanceData = _instanceDatas.back();
        instanceData->os.sync( command );
    }

    NodePtr node = command.getNode();
    node->send( CMD_NODE_SYNC_OBJECT_REPLY, useCache /*preferMulticast*/ )
        << node->getNodeID() << command.getObjectID() << command.getRequestID()
        << true << command.useCache() << useCache;
    return true;
}