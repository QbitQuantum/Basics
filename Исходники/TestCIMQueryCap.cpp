void testGetInstance(CIMClient& client, const char* ns)
{

   CIMInstance instance;
   Array<CIMKeyBinding> keyBindings;
   keyBindings.append(CIMKeyBinding(PROPERTY_NAME_INSTANCEID,
                                INSTANCEID_VALUE,
                                CIMKeyBinding::STRING));

   CIMObjectPath objectPath(String::EMPTY, ns,
                  CIM_QUERYCAPCLASS_NAME, keyBindings);

   instance = client.getInstance(ns, objectPath, false);

   Array<Uint16> providerReturnedVal;

   Uint32 prop = instance.findProperty(CIMName(PROPERTY_NAME_CQLFEATURES));
   instance.getProperty(prop).getValue().get(providerReturnedVal);

   _checkIfReturnedValueIsCorrect(providerReturnedVal);
}