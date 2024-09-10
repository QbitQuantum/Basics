// static
bool
PluginScriptableObjectParent::ScriptableEnumerate(NPObject* aObject,
                                                  NPIdentifier** aIdentifiers,
                                                  uint32_t* aCount)
{
  if (aObject->_class != GetClass()) {
    NS_ERROR("Don't know what kind of object this is!");
    return false;
  }

  ParentNPObject* object = reinterpret_cast<ParentNPObject*>(aObject);
  if (object->invalidated) {
    NS_WARNING("Calling method on an invalidated object!");
    return false;
  }

  ProtectedActor<PluginScriptableObjectParent> actor(object->parent);
  if (!actor) {
    return false;
  }

  NS_ASSERTION(actor->Type() == Proxy, "Bad type!");

  const NPNetscapeFuncs* npn = GetNetscapeFuncs(aObject);
  if (!npn) {
    NS_ERROR("No netscape funcs!");
    return false;
  }

  AutoInfallibleTArray<PPluginIdentifierParent*, 10> identifiers;
  bool success;
  if (!actor->CallEnumerate(&identifiers, &success)) {
    NS_WARNING("Failed to send message!");
    return false;
  }

  if (!success) {
    return false;
  }

  *aCount = identifiers.Length();
  if (!*aCount) {
    *aIdentifiers = nullptr;
    return true;
  }

  *aIdentifiers = (NPIdentifier*)npn->memalloc(*aCount * sizeof(NPIdentifier));
  if (!*aIdentifiers) {
    NS_ERROR("Out of memory!");
    return false;
  }

  for (uint32_t index = 0; index < *aCount; index++) {
    PluginIdentifierParent* id =
      static_cast<PluginIdentifierParent*>(identifiers[index]);
    (*aIdentifiers)[index] = id->ToNPIdentifier();
  }
  return true;
}