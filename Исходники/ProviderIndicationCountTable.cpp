void ProviderIndicationCountTable::getProviderKeys(
    const CIMInstance& providerInstance,
    String& providerModuleName,
    String& providerName)
{
    Array<CIMKeyBinding> keys = providerInstance.getPath().getKeyBindings();

    for (Uint32 i = 0; i < keys.size(); i++)
    {
        if (keys[i].getName() == PEGASUS_PROPERTYNAME_NAME)
        {
            providerName = keys[i].getValue();
        }
        else if (keys[i].getName() == _PROPERTY_PROVIDERMODULENAME)
        {
            providerModuleName = keys[i].getValue();
        }
    }
}