void TestCreateInstances(CIMClient& client)
{
    //
    // Test create Provider module instances
    //
    CIMObjectPath returnRef;

    CIMClass cimClass(CLASSNAME);

    CIMInstance cimInstance(CLASSNAME);

    cimInstance.addProperty(CIMProperty(CIMName ("Name"), 
        String("providersModule1")));
    cimInstance.addProperty(CIMProperty(CIMName ("Vendor"), String("HP")));
    cimInstance.addProperty(CIMProperty(CIMName ("Version"), String("2.0")));
    cimInstance.addProperty(CIMProperty(CIMName ("InterfaceType"), 
        String("C++Default")));
    cimInstance.addProperty(CIMProperty(CIMName ("InterfaceVersion"), 
        String("2.1.0")));
    cimInstance.addProperty(CIMProperty(CIMName ("Location"), 
        String("/tmp/module1")));

    CIMObjectPath instanceName = cimInstance.buildPath(cimClass);

    instanceName.setNameSpace(PEGASUS_NAMESPACENAME_INTEROP);
    instanceName.setClassName(CLASSNAME);

    try
    {
        returnRef = client.createInstance(PEGASUS_NAMESPACENAME_INTEROP, cimInstance);
    }
    catch(const CIMException&)
    {
        throw;
    }

    // Test create PG_Provider instances

    CIMObjectPath returnRef2;

    CIMClass cimClass2(CLASSNAME2);

    CIMInstance cimInstance2(CLASSNAME2);

    cimInstance2.addProperty(CIMProperty(CIMName ("ProviderModuleName"), 
        String("providersModule1")));
    cimInstance2.addProperty(CIMProperty(CIMName ("Name"), 
        String("PG_ProviderInstance1")));

    CIMObjectPath instanceName2 = cimInstance2.buildPath(cimClass2);

    instanceName2.setNameSpace(PEGASUS_NAMESPACENAME_INTEROP);
    instanceName2.setClassName(CLASSNAME2);

    try
    {
        returnRef2 = client.createInstance(PEGASUS_NAMESPACENAME_INTEROP, cimInstance2);
    }
    catch(const CIMException&)
    {
        throw;
    }

    //
    // test create provider capability instances
    //

    Array <String> namespaces;
    Array <Uint16> providerType;
    Array <String> supportedMethods;
    Array <String> supportedProperties;

    namespaces.append("root/cimv2");
    namespaces.append("root/cimv3");
    
    providerType.append(4);
    providerType.append(5);

    supportedMethods.append("test_method1");
    supportedMethods.append("test_method2");

    supportedProperties.append("PkgStatus");
    supportedProperties.append("PkgIndex");

    CIMObjectPath returnRef3;

    CIMClass cimClass3(CLASSNAME3);

    CIMInstance cimInstance3(CLASSNAME3);

    cimInstance3.addProperty(CIMProperty(CIMName ("ProviderModuleName"), 
        String("providersModule1")));
    cimInstance3.addProperty(CIMProperty(CIMName ("ProviderName"), 
        String("PG_ProviderInstance1")));
    cimInstance3.addProperty(CIMProperty(CIMName ("CapabilityID"), 
        String("capability1")));
    cimInstance3.addProperty(CIMProperty(CIMName ("ClassName"), 
        String("TestSoftwarePkg")));
    cimInstance3.addProperty(CIMProperty(CIMName ("Namespaces"), namespaces));
    cimInstance3.addProperty(CIMProperty(CIMName ("ProviderType"), 
        providerType));
    cimInstance3.addProperty(CIMProperty(CIMName ("SupportedMethods"), 
        supportedMethods));
    cimInstance3.addProperty(CIMProperty(CIMName ("SupportedProperties"), 
        supportedProperties));

    CIMObjectPath instanceName3 = cimInstance3.buildPath(cimClass3);

    instanceName3.setNameSpace(PEGASUS_NAMESPACENAME_INTEROP);
    instanceName3.setClassName(CLASSNAME3);

    try
    {
        returnRef3 = client.createInstance(PEGASUS_NAMESPACENAME_INTEROP, cimInstance3);
    }
    catch(const CIMException&)
    {
        throw;
    }

    CIMKeyBinding kb1(CIMName ("Name"), "providersModule1", 
        CIMKeyBinding::STRING);
    Array<CIMKeyBinding> keys;
    keys.append(kb1);

    instanceName.setKeyBindings(keys);

    // test getInstance
    try
    {
    	client.getInstance(PEGASUS_NAMESPACENAME_INTEROP, instanceName);
    }
    catch(const CIMException&)
    {
        throw;
    }

    // test enumerateInstances
    try
    {
    	client.enumerateInstances(PEGASUS_NAMESPACENAME_INTEROP, PEGASUS_CLASSNAME_PROVIDER);
    }
    catch(const CIMException&)
    {
        throw;
    }

    // test enumerateInstanceNames
    try
    {
    	client.enumerateInstanceNames(PEGASUS_NAMESPACENAME_INTEROP, PEGASUS_CLASSNAME_PROVIDER);
    }
    catch(const CIMException&)
    {
        throw;
    }


    client.deleteInstance(PEGASUS_NAMESPACENAME_INTEROP, instanceName);
}