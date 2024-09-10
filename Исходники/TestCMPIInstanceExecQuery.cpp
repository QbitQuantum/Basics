void _test4(CIMClient & client)
{
    static const String NAMESPACE("test/TestProvider");
    static const String CLASSNAME("cmpiPerf_TestClassA");
    Array<CIMObjectPath> cimInstanceNames =
    client.enumerateInstanceNames(
        NAMESPACE,
        CLASSNAME);
    cout<<"+++++++++empty property list filtered output++++++"<<endl;
    {
        Array<CIMName> propNames;
        for (Uint32 i = 0, n = cimInstanceNames.size(); i < n; i++)
        {
            CIMInstance cimInstance=client.getInstance(
                NAMESPACE,
                cimInstanceNames[i],
                true,
                false,
                false,
                CIMPropertyList(propNames));
            if (verbose)
            {
                XmlWriter::printInstanceElement(cimInstance);
            }
            Uint32 propertyCount = cimInstance.getPropertyCount();
            if(propertyCount == 0)
            {
                cout<<"Filter getInstance test on "
                    <<"cmpiPerf_TestClassA SUCCEEDED :Filtering "
                    <<"the ciminstance with a empty property list "
                    <<"returned zero properties as expected"<<endl;
            }
            else
            {
                cout<<"Filter getInstance test on cmpiPerf_TestClassA"
                    <<" FAILED:Filtering the ciminstance with a empty "
                    <<"property list returned some properties "
                    <<"which is not expected"<<endl;
                PEGASUS_TEST_ASSERT(false);
            } 
        }
    }
    cout<<"+++++++++wrong property list filtered output++++++"<<endl;
    {
        Array<CIMName> propNames;
        propNames.append(CIMName(String("theK")));
        for (Uint32 i = 0, n = cimInstanceNames.size(); i < n; i++)
        {
            CIMInstance cimInstance=client.getInstance(
                NAMESPACE,
                cimInstanceNames[i],
                true,
                false,
                false,
                CIMPropertyList(propNames));
            if (verbose)
            {
                XmlWriter::printInstanceElement(cimInstance);
            }
            Uint32 propertyCount = cimInstance.getPropertyCount();
            if(propertyCount == 0)
            {
                cout<<"Filter getInstance test on "
                    <<"cmpiPerf_TestClassA SUCCEEDED :Filtering "
                    <<"the ciminstance with a wrong property list "
                    <<"returned zero properties as expected"<<endl;
            }
            else
            {
                cout<<"Filter getInstance test on cmpiPerf_TestClassA"
                    <<" FAILED:Filtering the ciminstance with a wrong "
                    <<"property list returned some properties "
                    <<"which is not expected"<<endl;
                PEGASUS_TEST_ASSERT(false);
            }
        }
    }
    cout<<"+++++++++NULL property list filtered output++++++"<<endl;
    {
        for (Uint32 i = 0, n = cimInstanceNames.size(); i < n; i++)
        {
            CIMInstance cimInstance=client.getInstance(
                NAMESPACE,
                cimInstanceNames[i],
                true,
                false,
                false,
                CIMPropertyList());
            if (verbose)
            {
                XmlWriter::printInstanceElement(cimInstance);
            }
            Uint32 propertyCount = cimInstance.getPropertyCount();
            if(propertyCount == 24)
            {
                cout<<"Filter getInstance test on "
                    <<"cmpiPerf_TestClassA SUCCEEDED :Filtering "
                    <<"the ciminstance with a NULL property list "
                    <<"returned all properties as expected"<<endl;
            }
            else
            {
                cout<<"Filter getInstance test on cmpiPerf_TestClassA"
                    <<" FAILED:Filtering the ciminstance with a NULL "
                    <<"property list did not return all properties "
                    <<"as expected"<<endl;
                PEGASUS_TEST_ASSERT(false);
            }
        }
    }
    cout<<"+++++++++mentioned  property list filtered output++++++"<<endl;
    {
        Array<CIMName> propNames;
        propNames.append(CIMName(String("RequestedState")));
        propNames.append(CIMName(String("theKey")));
        for (Uint32 i = 0, n = cimInstanceNames.size(); i < n; i++)
        {
            CIMInstance cimInstance=client.getInstance(
                NAMESPACE,
                cimInstanceNames[i],
                true,
                false,
                false,
                CIMPropertyList(propNames));
            if (verbose)
            {
                XmlWriter::printInstanceElement(cimInstance);
            }
            Uint32 propertyCount = cimInstance.getPropertyCount();
            Uint32 propNameCount = 0;
            for(Uint32 j=0;j<propertyCount;j++)
            {
                String propName=
                    cimInstance.getProperty(j).getName().
                    getString();
                if((propName == "RequestedState")||(propName == "theKey"))
                {
                    propNameCount++;
                }
            } 
            if((propertyCount == 2) && (propNameCount == 2))
            {
                cout<<"Filter getInstance test on "
                    <<"cmpiPerf_TestClassA SUCCEEDED :Filtering "
                    <<"the ciminstance with a mentioned property list "
                    <<"returned all properties as expected"<<endl;
            }
            else
            {
                cout<<"Filter getInstance test on cmpiPerf_TestClassA"
                    <<" FAILED:Filtering the ciminstance with a mentioned "
                    <<"property list did not return all properties "
                    <<"as expected"<<endl;
                PEGASUS_TEST_ASSERT(false);
            }
        }
    } 
}