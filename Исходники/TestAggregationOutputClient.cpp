void getPropertiesFromCIMServer(
    CIMClient& client,
    const CIMName& propName,
    Array <String>& propValues)
{
    CIMProperty prop;

    Array<CIMKeyBinding> kbArray;
    CIMKeyBinding        kb;
    String               _hostName;

    kb.setName(PROPERTY_NAME);
    kb.setValue(propName.getString());
    kb.setType(CIMKeyBinding::STRING);

    _hostName.assign(System::getHostName());

    kbArray.append(kb);

    CIMObjectPath reference(_hostName, PEGASUS_NAMESPACENAME_CONFIG,
                            PEGASUS_CLASSNAME_CONFIGSETTING, kbArray);

    CIMInstance cimInstance = client.getInstance(PEGASUS_NAMESPACENAME_CONFIG,
                                                 reference);

    Uint32 pos = cimInstance.findProperty(PROPERTY_NAME);
    prop = (CIMProperty)cimInstance.getProperty(pos);
    propValues.append(prop.getValue().toString());

    pos = cimInstance.findProperty(DEFAULT_VALUE);
    prop = (CIMProperty)cimInstance.getProperty(pos);
    propValues.append(prop.getValue().toString());

    pos = cimInstance.findProperty(CURRENT_VALUE);
    prop = (CIMProperty)cimInstance.getProperty(pos);
    propValues.append(prop.getValue().toString());

    pos = cimInstance.findProperty(PLANNED_VALUE);
    prop = (CIMProperty)cimInstance.getProperty(pos);
    propValues.append(prop.getValue().toString());

    pos = cimInstance.findProperty(DYNAMIC_PROPERTY);
    prop = (CIMProperty)cimInstance.getProperty(pos);
    propValues.append(prop.getValue().toString());

}