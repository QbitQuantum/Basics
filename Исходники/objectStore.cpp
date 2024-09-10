void ObjectStore::unmapObject( Object* object )
{
    EQASSERT( object );
    if( !object->isAttached( )) // not registered
        return;

    const base::UUID& id = object->getID();
    
    EQLOG( LOG_OBJECTS ) << "Unmap " << object << std::endl;

    object->notifyDetach();

    // send unsubscribe to master, master will send detach packet.
    EQASSERT( !object->isMaster( ));
    EQ_TS_NOT_THREAD( _commandThread );
    
    const uint32_t masterInstanceID = object->getMasterInstanceID();
    if( masterInstanceID != EQ_INSTANCE_INVALID )
    {
        NodePtr master = object->getMasterNode();
        EQASSERT( master )

        if( master.isValid() && master->isConnected( ))
        {
            NodeUnsubscribeObjectPacket packet;
            packet.requestID = _localNode->registerRequest();
            packet.objectID  = id;
            packet.masterInstanceID = masterInstanceID;
            packet.slaveInstanceID  = object->getInstanceID();
            master->send( packet );

            _localNode->waitRequest( packet.requestID );
            object->notifyDetached();
            return;
        }
        EQERROR << "Master node for object id " << id << " not connected"
                << std::endl;
    }