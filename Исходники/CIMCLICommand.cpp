Boolean setObjectManagerStatistics(CIMClient & client, Boolean newState)
{

    CIMName gathStatName ("GatherStatisticalData");
    Array<CIMInstance> instancesObjectManager;
    CIMInstance instObjectManager;
    Uint32 prop_num;
    Array<CIMName> plA;
    plA.append(gathStatName);
    CIMPropertyList statPropertyList(plA);
    // Create property list that represents correct request
    // get instance.  Get only the gatherstatitistics property
    instancesObjectManager  = 
        client.enumerateInstances(PEGASUS_NAMESPACENAME_INTEROP,
            "CIM_ObjectManager",
            true, false, false, false, statPropertyList);
    PEGASUS_TEST_ASSERT(instancesObjectManager.size() == 1);
    instObjectManager = instancesObjectManager[0];
    // set correct path into instance
    instObjectManager.setPath(instancesObjectManager[0].getPath());
    
    prop_num = instObjectManager.findProperty(gathStatName);
    PEGASUS_TEST_ASSERT(prop_num != PEG_NOT_FOUND);
    
    instObjectManager.getProperty(prop_num).setValue(CIMValue(newState));
    
    client.modifyInstance(PEGASUS_NAMESPACENAME_INTEROP, instObjectManager,
         false, statPropertyList);
    CIMInstance updatedInstance = 
        client.getInstance(PEGASUS_NAMESPACENAME_INTEROP,
        instObjectManager.getPath(),
        false, false, false, statPropertyList);
    prop_num = updatedInstance.findProperty(gathStatName);
    PEGASUS_TEST_ASSERT(prop_num != PEG_NOT_FOUND);
    CIMProperty p = updatedInstance.getProperty(prop_num);
    CIMValue v = p.getValue();
    Boolean rtn;
    v.get(rtn);
    //// Need to get it again
    cout << "Updated Status= " << ((rtn)? "true" : "false") << endl;
    return(rtn);
}