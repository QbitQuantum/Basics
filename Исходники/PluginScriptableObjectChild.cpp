// static
bool
PluginScriptableObjectChild::ScriptableEnumerate(NPObject* aObject,
                                                 NPIdentifier** aIdentifiers,
                                                 uint32_t* aCount)
{
  AssertPluginThread();

  if (aObject->_class != GetClass()) {
    NS_RUNTIMEABORT("Don't know what kind of object this is!");
  }

  ChildNPObject* object = reinterpret_cast<ChildNPObject*>(aObject);
  if (object->invalidated) {
    NS_WARNING("Calling method on an invalidated object!");
    return false;
  }

  ProtectedActor<PluginScriptableObjectChild> actor(object->parent);
  NS_ASSERTION(actor, "This shouldn't ever be null!");
  NS_ASSERTION(actor->Type() == Proxy, "Bad type!");

  AutoInfallibleTArray<PPluginIdentifierChild*, 10> identifiers;
  bool success;
  actor->CallEnumerate(&identifiers, &success);

  if (!success) {
    return false;
  }

  *aCount = identifiers.Length();
  if (!*aCount) {
    *aIdentifiers = nsnull;
    return true;
  }

  *aIdentifiers = reinterpret_cast<NPIdentifier*>(
      PluginModuleChild::sBrowserFuncs.memalloc(*aCount * sizeof(NPIdentifier)));
  if (!*aIdentifiers) {
    NS_ERROR("Out of memory!");
    return false;
  }

  for (PRUint32 index = 0; index < *aCount; index++) {
    (*aIdentifiers)[index] =
      static_cast<PPluginIdentifierChild*>(identifiers[index]);
  }
  return true;
}