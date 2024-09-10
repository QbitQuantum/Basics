int main(int argc, char** argv)
{
    cout << "+++++ testing Client Performance Statistics" << endl;

    try
    {
        // connecting to server
        CIMClient client;
        client.connect("localhost", 5988, String::EMPTY, String::EMPTY);

        // the value CIM_ObjectManager::GatherStatisticalData must be set to
        // true.  the following code does this
        String className = "CIM_ObjectManager";
        CIMName cN = CIMName(className);
        Boolean loc = true;
        String gath = "GatherStatisticalData";
        CIMName gst = CIMName(gath);
        CIMValue val = CIMValue(loc);
        Array<CIMObjectPath> instanceNames;
        /* EnumerateInstances and
        */
        try
        {
            instanceNames = client.enumerateInstanceNames(
                PEGASUS_NAMESPACENAME_INTEROP, cN);
        }
        catch (Exception& e)
        {
            cerr << "Exception : " << e.getMessage() << endl;
            exit(1);
        }
        catch (...)
        {
            cout << "enumerateInstancesNames in Client/tests/ClientStatistics "
                "has thrown an exception" << endl;
            exit(1);
        }
        // assert that we received  one name
        PEGASUS_TEST_ASSERT(instanceNames.size() == 1);
        /* ModifyInstance
        */
        CIMName gathStatName ("GatherStatisticalData");

        // variables used with gatherstatistics setting.
        CIMInstance instObjectManager;
        Uint32 prop_num;
        Array<CIMName> plA;
        plA.append(gathStatName);
        CIMPropertyList statPropertyList(plA);
        try
        {
            // Create property list that represents correct request
            // get instance.  Get only the gatherstatitistics property
            instObjectManager = client.getInstance(
                PEGASUS_NAMESPACENAME_INTEROP,
                instanceNames[0],
                true,
                false,
                false,
                statPropertyList);
            // set correct path into instance
            instObjectManager.setPath(instanceNames[0]);

            prop_num = instObjectManager.findProperty(gathStatName);
            PEGASUS_TEST_ASSERT(prop_num != PEG_NOT_FOUND);

            instObjectManager.getProperty(prop_num).setValue(CIMValue(true));

            client.modifyInstance(
                PEGASUS_NAMESPACENAME_INTEROP,
                instObjectManager,
                false,
                statPropertyList);
        }
        catch (Exception& e)
        {
            cerr << "Exception : " << e.getMessage() << endl;
            exit(1);
        }

        //registering class that has the callback method
        CliStat stat = CliStat();
        client.registerClientOpPerformanceDataHandler(stat);
        String classN = "PG_ComputerSystem";
        Array<CIMObjectPath> instance = client.enumerateInstanceNames(
            PEGASUS_NAMESPACENAME_CIMV2,
            classN);
        instObjectManager.getProperty(prop_num).setValue(CIMValue(false));
        client.modifyInstance(
            PEGASUS_NAMESPACENAME_INTEROP,
            instObjectManager,
            false,
            statPropertyList);
    }
    catch (Exception& e)
    {
        cerr << "Error: " << e.getMessage() << endl;
        exit(1);
    }

    cout << "+++++ passed all tests" << endl;

    return 0;
}