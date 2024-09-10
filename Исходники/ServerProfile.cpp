void testAssociationClass(CIMClient & client, const CIMName & className)
{
    cout << "Testing Association Class "
        << (const char *)className.getString().getCString()
        << "...";
    Array<CIMInstance> instances = testAnyClass(client, className);

    for(unsigned int i = 0, n = instances.size(); i < n; ++i)
    {
        //
        // Now make sure that the references are valid and that association
        // traversal between them is working properly.
        //
        CIMObjectPath referenceA;
        CIMObjectPath referenceB;
        CIMInstance currentInstance = instances[i];
        CIMObjectPath currentInstanceName = currentInstance.getPath();
        if(currentInstanceName.getNameSpace().isNull())
            currentInstanceName.setNameSpace(interopNamespace);

        for(unsigned int j = 0, m = currentInstance.getPropertyCount();
            j < m; ++j)
        {
            CIMProperty currentProp = currentInstance.getProperty(j);
            if(currentProp.getValue().getType() == CIMTYPE_REFERENCE)
            {
                if(referenceA.getKeyBindings().size() == 0)
                {
                    currentProp.getValue().get(referenceA);
                }
                else
                {
                    currentProp.getValue().get(referenceB);
                    break;
                }
            }
        }

        if(referenceA.getKeyBindings().size() == 0 ||
            referenceB.getKeyBindings().size() == 0)
        {
            exitFailure(
                String("Could not find reference properties for ") +
                String("association: ") +
                currentInstanceName.toString());
        }

        try
        {
            client.getInstance(referenceA.getNameSpace(), referenceA);
            client.getInstance(referenceB.getNameSpace(), referenceB);
        }
        catch(CIMException &)
        {
            exitFailure(String("Could not get instances for association : ") +
                currentInstanceName.toString());
        }

        Boolean associationFailure = false;
        try
        {
            Array<CIMObjectPath> results = client.associatorNames(
                referenceA.getNameSpace(), referenceA, className);
            Boolean found = false;
            for(unsigned int j = 0, m = results.size(); j < m; ++j)
            {
                CIMObjectPath result = results[j];
                result.setHost(referenceB.getHost());
                result.setNameSpace(referenceB.getNameSpace());
                if(result == referenceB)
                {
                    found = true;
                    break;
                }
            }

            if(found)
            {
                results = client.associatorNames(referenceB.getNameSpace(),
                    referenceB, className);
                for(unsigned int j = 0, m = results.size(); j < m; ++j)
                {
                    CIMObjectPath result = results[j];
                    result.setHost(referenceA.getHost());
                    result.setNameSpace(referenceA.getNameSpace());
                    if(result == referenceA)
                    {
                        found = true;
                        break;
                    }
                }
            }

            if(!found)
            {
                associationFailure = true;
            }
        }
        catch(CIMException & e)
        {
            cout << "Exception: " << e.getMessage() << endl;
            associationFailure = true;
        }

        if(associationFailure)
        {
            exitFailure(String("Association traversal failed between ") +
                String("instances of association: ") +
                currentInstanceName.toString());
        }

        Boolean referencesFailure = false;
        try
        {
            Array<CIMObjectPath> results = client.referenceNames(
                referenceA.getNameSpace(), referenceA, className);
            Boolean found = false;
            for(unsigned int j = 0, m = results.size(); j < m; ++j)
            {
                CIMObjectPath currentPath = results[j];
                if(currentPath.getNameSpace().isNull())
                    currentPath.setNameSpace(interopNamespace);
                if(currentPath.getHost().size() != 0)
                    currentPath.setHost(String::EMPTY);
                if(currentPath == currentInstanceName)
                {
                    found = true;
                    break;
                }
            }

            if(found)
            {
                results = client.referenceNames(referenceB.getNameSpace(),
                    referenceB, className);
                for(unsigned int j = 0, m = results.size(); j < m; ++j)
                {
                    CIMObjectPath currentPath = results[j];
                    if(currentPath.getNameSpace().isNull())
                        currentPath.setNameSpace(interopNamespace);
                    if(currentPath.getHost().size() != 0)
                        currentPath.setHost(String::EMPTY);
                    if(currentPath == currentInstanceName)
                    {
                        found = true;
                        break;
                    }
                }
            }

            if(!found)
            {
                referencesFailure = true;
            }
        }
        catch(CIMException &)
        {
            referencesFailure = true;
        }

        if(referencesFailure)
        {
            exitFailure(String("References operation failed for ") +
                String("instances of association: ") +
                currentInstanceName.toString());
        }
    }

    cout << "Test Complete" << endl;
}