static void TestNamespaceHierarchy1 ( CIMClient& client,
                        Boolean activeTest,
                        Boolean verboseTest)
{
    Array<CIMNamespaceName> namespaces;
    String instanceName;

    namespaces.append(CIMNamespaceName ("test1"));
    namespaces.append(CIMNamespaceName ("test2"));
    namespaces.append(CIMNamespaceName ("test3"));
    namespaces.append(CIMNamespaceName ("test4"));
    namespaces.append(CIMNamespaceName ("test5"));
    namespaces.append(CIMNamespaceName ("test6"));
    namespaces.append(CIMNamespaceName ("test1/test2"));
    namespaces.append(CIMNamespaceName ("test1/test2/test3"));
    namespaces.append(CIMNamespaceName ("test1/test2/test3/test4"));
    namespaces.append(CIMNamespaceName ("test1/test2/test3/test4/test5"));
    namespaces.append(CIMNamespaceName ("test1/test2/test3/test4/test5/test6"));
    if(verboseTest)
    {
      cout << "++ Cleanup existing test namespaces" << endl;
    }
    for (Sint32 i = namespaces.size()-1; i > -1; i--)
    {
      // Build the instance name for __namespace
      CIMNamespaceName testNamespaceName = namespaces[i];
      instanceName.clear();
      instanceName.append(CLASSNAME.getString());
      instanceName.append( ".Name=\"");
      instanceName.append(testNamespaceName.getString());
      instanceName.append("\"");

      try
    {
      CIMObjectPath myReference(instanceName);
      if(verboseTest)
        cout << "Deleting " << testNamespaceName << endl;
      client.deleteInstance(__NAMESPACE_NAMESPACE, myReference);
    }
      catch(...)
      {
      //Ignore errors we are just trying to cleanup
      }
    }

    if(verboseTest)
    {
      cout << "++ Create test namespaces" << endl;
    }
    for (Uint32 i = 0; i < namespaces.size(); i++)
      {
    // Build the instance name for __namespace
    CIMNamespaceName testNamespaceName = namespaces[i];
    String instanceName = CLASSNAME.getString();
    instanceName.append( ".Name=\"");
    instanceName.append(testNamespaceName.getString());
    instanceName.append("\"");
    if(verboseTest)
    {
        cout << "Creating " << testNamespaceName << endl;
    }
    try
    {
        // Build the new instance
        CIMInstance newInstance(CLASSNAME);
        newInstance.addProperty(CIMProperty(CIMName ("name"),
                testNamespaceName.getString()));
        client.createInstance(__NAMESPACE_NAMESPACE, newInstance);
    }
    catch(Exception& e)
    {
         PEGASUS_STD(cerr) << "Exception NameSpace Creation: "
            << e.getMessage() << " Creating " << instanceName
                << PEGASUS_STD(endl);
         exit(1);
    }
      }

    for (Sint32 i = namespaces.size()-1; i > -1; i--)
    {
      // Build the instance name for __namespace
      CIMNamespaceName testNamespaceName = namespaces[i];
      instanceName.clear();
      instanceName.append(CLASSNAME.getString());
      instanceName.append( ".Name=\"");
      instanceName.append(testNamespaceName.getString());
      instanceName.append("\"");

      try
    {
      CIMObjectPath myReference(instanceName);
      if(verboseTest)
        cout << "getInstance " << testNamespaceName << endl;
      CIMInstance namespaceInstance = client.getInstance(__NAMESPACE_NAMESPACE, myReference);
    }
      catch(Exception& e)
    {
      PEGASUS_STD(cerr) << "Exception NameSpace Deletion1: "
                << e.getMessage() << " Deleting " << instanceName
                << PEGASUS_STD(endl);
      exit(1);
    }
    }

  if(verboseTest)
    cout << "++ Delete test namespaces " << endl;

  for (Sint32 i = namespaces.size()-1; i > -1; i--)
    {
      // Build the instance name for __namespace
      CIMNamespaceName testNamespaceName = namespaces[i];
      instanceName.clear();
      instanceName.append(CLASSNAME.getString());
      instanceName.append( ".Name=\"");
      instanceName.append(testNamespaceName.getString());
      instanceName.append("\"");

      try
    {
      CIMObjectPath myReference(instanceName);
      if(verboseTest)
        cout << "Deleting " << testNamespaceName << endl;
      client.deleteInstance(__NAMESPACE_NAMESPACE, myReference);
    }
      catch(Exception& e)
    {
      PEGASUS_STD(cerr) << "Exception NameSpace Deletion 2: "
                << e.getMessage() << " Deleting " << instanceName
                << PEGASUS_STD(endl);
      exit(1);
    }
    }
}