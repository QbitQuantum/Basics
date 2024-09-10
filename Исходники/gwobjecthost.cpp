void GwObjectHost::assignClientMessageObjectsGwIds(const Signature& signature, Message& msg, TransportSocketPtr sender)
{
  // if there's no chance of any object being in the call we're done.
  if (!hasObjectsSomewhere(signature))
    return;

  AnyReference callParameters = msg.value(signature, sender);

  // re-serialize the arguments so that the objects can receive a GW-specific objectId
  // ObjectHost uses a static int for its objectId so we're OK instantiating multiple
  // ones.
  Message forward;
  MockObjectHost host(Message::Service_Server);

  forward.setFlags(msg.flags());
  forward.setValue(callParameters, signature, &host, sender.get());
  msg.setBuffer(forward.buffer());

  // The message will store all the objects it serializes in the host.
  const ObjectHost::ObjectMap& objects = host.objects();
  std::map<GwObjectId, MetaObject> newObjectsMetaObjects;
  std::map<GwObjectId, std::pair<TransportSocketPtr, ObjectAddress> > newObjectsOrigin;
  std::map<ObjectAddress, GwObjectId> newHostObjectBank;
  for (ObjectHost::ObjectMap::const_iterator it = objects.begin(), end = objects.end(); it != end; ++it)
  {
    GwObjectId oid = it->first;
    ServiceBoundObject* sbo = static_cast<ServiceBoundObject*>(it->second.get());
    RemoteObject* ro = static_cast<RemoteObject*>(sbo->object().asGenericObject()->value);
    ObjectAddress addr;
    addr.service = ro->service();
    addr.object = ro->object();
    ro->setTransportSocket(TransportSocketPtr());

    newObjectsMetaObjects[oid] = ro->metaObject();
    newObjectsOrigin[oid] = std::make_pair(sender, addr);
    newHostObjectBank[addr] = oid;
    // We set an empty transportsocket.
    // Otherwise when we destroy `passed` below, the remoteobject
    // will attempt to send back home a `terminate` message, which we don't want.
    // By setting a null socket the object will stay alive on the remote end.

    qiLogDebug() << "Message " << msg.address() << ", Object connection: {" << addr.service << "," << addr.object
                 << "} <=> {0," << oid << "}";
  }
  {
    boost::upgrade_lock<boost::shared_mutex> lock(_mutex);
    boost::upgrade_to_unique_lock<boost::shared_mutex> unique_lock(lock);
    _objectsMetaObjects.insert(newObjectsMetaObjects.begin(), newObjectsMetaObjects.end());
    _objectsOrigin.insert(newObjectsOrigin.begin(), newObjectsOrigin.end());
    _hostObjectBank[sender].insert(newHostObjectBank.begin(), newHostObjectBank.end());
  }
  callParameters.destroy();
}