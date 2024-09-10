int retrieveErrorInstance(CIMClient& client)
{
    try
    {
        PEGASUS_STD(cout) << "Getting error instance: " << errorPath.toString()
            << PEGASUS_STD(endl);
        CIMInstance ret = client.getInstance(
            TEST_NAMESPACE, errorPath, true, false, false, errorPropList);
        ret.setPath(errorPath);
        if (!errorInstance->identical(ret))
        {
            if (!ret.getPath().identical(errorInstance->getPath()))
            {
                PEGASUS_STD(cout) << "Object Paths not identical"
                    << PEGASUS_STD(endl);
            }
            PEGASUS_STD(cout) << "Error Instance and instance retrieved "
                << "through GetInstance operation not the same\n"
                << PEGASUS_STD(endl);
            PEGASUS_STD(cout) << "Local Error Instance: "
                << errorInstance->getPath().toString() << PEGASUS_STD(endl);
            for (unsigned int i = 0, n = errorInstance->getPropertyCount();
                 i < n; i++)
            {
                CIMProperty prop = errorInstance->getProperty(i);
                PEGASUS_STD(cout) << i << ". " << prop.getName().getString()
                    << prop.getValue().toString() << PEGASUS_STD(endl);
            }

            PEGASUS_STD(cout) << "Retrieved Error Instance: " <<
                ret.getPath().toString() << PEGASUS_STD(endl);
            for (unsigned int i = 0, n = ret.getPropertyCount();
                 i < n; i++)
            {
                CIMProperty prop = ret.getProperty(i);
                PEGASUS_STD(cout) << i << ". " << prop.getName().getString()
                    << prop.getValue().toString() << PEGASUS_STD(endl);
            }

            CIMProperty localEmbeddedProp = errorInstance->getProperty(
                errorInstance->findProperty("EmbeddedInst"));
            CIMProperty retEmbeddedProp = ret.getProperty(
                ret.findProperty("EmbeddedInst"));
            CIMInstance localEmbeddedInst;
            CIMInstance retEmbeddedInst;
            localEmbeddedProp.getValue().get(localEmbeddedInst);
            retEmbeddedProp.getValue().get(retEmbeddedInst);
            CIMObjectPath localEmbeddedPath = localEmbeddedInst.getPath();
            CIMObjectPath retEmbeddedPath = retEmbeddedInst.getPath();

            PEGASUS_STD(cout) << "Local Embedded Path: " <<
                localEmbeddedPath.toString() << PEGASUS_STD(endl);
            PEGASUS_STD(cout) << "Ret Embedded Path: " <<
                retEmbeddedPath.toString() << PEGASUS_STD(endl);
            return -1;
        }
    }
    catch (Exception& e)
    {
        cout << "Exception caught while getting error instance: "
            << e.getMessage() << endl;
        return -1;
    }

    try
    {
        Array<CIMInstance> ret = client.enumerateInstances(
            TEST_NAMESPACE,
            "PG_EmbeddedError",
            true,
            true,
            false,
            false,
            errorPropList);
        int count = ret.size();
        for (int i = 0; i < count; i++)
        {
            if (!errorInstance->identical(ret[i]))
            {
                printf("Error instance and instance retrieved through "
                    "EnumerateInstances operation not the same\n");
                return -1;
            }
        }
    }
    catch (Exception& e)
    {
        cout << "Exception caught while enumerating error instances: "
            << e.getMessage() << endl;
        return -1;
    }

    return 0;
}