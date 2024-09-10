//
// Enumerates all of the ElementConformsToProfile association instances.
//
Array<CIMInstance> InteropProvider::enumElementConformsToProfileInstances(
    const OperationContext & opContext, const CIMNamespaceName & opNamespace)
{
    CIMClass elementConformsClass = repository->getClass(
        PEGASUS_NAMESPACENAME_INTEROP,
        PEGASUS_CLASSNAME_PG_ELEMENTCONFORMSTOPROFILE,
        false, true, false);

    AutoMutex holder(interopMut);
    Array<CIMInstance> instances;
    verifyCachedInfo();
    // Loop through the cached profile Id's and related info about its
    // conforming elements.
    for (Uint32 i = 0, n = profileIds.size(); i < n; ++i)
    {
        String & profileId = profileIds[i];
        Array<CIMName> & elementList = conformingElements[i];
        Array<CIMNamespaceName> & namespaceList = elementNamespaces[i];
        Array<CIMObjectPath> conformingElementPaths;
        for (Uint32 j = 0, m = elementList.size(); j < m; ++j)
        {
            CIMName & currentElement = elementList[j];
            CIMNamespaceName & currentNamespace = namespaceList[j];

            if (opNamespace == PEGASUS_NAMESPACENAME_INTEROP ||
                opNamespace == currentNamespace)
            {
                String currentElementStr(currentElement.getString());
                if (currentElementStr.find(PEGASUS_DYNAMIC) == 0)
                {
                    // If the provider profile registration did not provide a
                    // list of conforming elements (presumably because there is
                    // no such definite list), then the provider is required
                    // to provide instances of ElementConformsToProfile in the
                    // vendor namespace, so we do not generate instances.
                    if (opNamespace != PEGASUS_NAMESPACENAME_INTEROP)
                    {
                        continue;
                    }
                    CIMName subclassName(
                        currentElementStr.subString(PEGASUS_DYNAMIC_LEN));
                    Array<CIMInstance> elementConformsInstances =
                        cimomHandle.enumerateInstances(opContext,
                        currentNamespace, subclassName, true, false, false,
                        true, CIMPropertyList());

                    // Retrieve the Conforming Element
                    for (Uint32 k = 0, x = elementConformsInstances.size();
                        k < x; ++k)
                    {
                        CIMInstance & currentInstance =
                            elementConformsInstances[k];

                        // NOCHKSRC
                        // Make sure that the current instance points to the
                        // current profile ID.
                        CIMObjectPath profilePath =
                            getRequiredValue<CIMObjectPath>(
                                elementConformsInstances[k],
                                ELEMENTCONFORMSTOPROFILE_PROPERTY_CONFORMANTSTANDARD);
                        // DOCHKSRC
                        const Array<CIMKeyBinding> & keys =
                            profilePath.getKeyBindings();
                        if (keys.size() != 1)
                            continue;
                        if (keys.size() == 1 && keys[0].getValue() == profileId)
                        {
                            // NOCHKSRC
                            conformingElementPaths.append(
                                getRequiredValue<CIMObjectPath>(
                                currentInstance,
                                ELEMENTCONFORMSTOPROFILE_PROPERTY_MANAGEDELEMENT));
                            // DOCHKSRC
                        }
                    }
                }
                else
                {
                    // All of the instances of the current element in the
                    // corresponding namespace conform to the current profile.
                    Array<CIMObjectPath> paths =
                        cimomHandle.enumerateInstanceNames(opContext,
                            currentNamespace, currentElement);
                    // Set the namespace in the paths just in case
                    for (Uint32 k = 0, x = paths.size();
                        k < x; ++k)
                    {
                        CIMObjectPath & curPath = paths[k];
                        curPath.setNameSpace(currentNamespace);
                        curPath.setHost(hostName);
                    }
                    conformingElementPaths.appendArray(paths);
                }
            }
        }

        // Create the object path for the RegisteredProfile using the given
        // profileId.
        CIMObjectPath profilePath = buildDependencyReference(
            hostName, profileIds[i], PEGASUS_CLASSNAME_PG_REGISTEREDPROFILE);

        // Build all of the ElementConformsToProfile instances for the current
        // profile.
        for (Uint32 k = 0, x = conformingElementPaths.size(); k < x; ++k)
        {
            instances.append(buildElementConformsToProfile(profilePath,
                conformingElementPaths[k], elementConformsClass));
        }
    }

    // Now add the default instance: the association between the Server Profile
    // and the ObjectManager (if we're in the Interop namespace)
    if (opNamespace == PEGASUS_NAMESPACENAME_INTEROP)
    {
        // Build up the Object Path for the server profile version 1.1.0
        CIMObjectPath serverProfile = buildDependencyReference(
            hostName,
            buildProfileInstanceId(SNIA_NAME, "Server", SNIA_VER_110),
            PEGASUS_CLASSNAME_PG_REGISTEREDPROFILE);
        // Retrieve the Object Manager instance
        CIMInstance objManager = getObjectManagerInstance();

        instances.append(
            buildElementConformsToProfile(
                serverProfile,
                objManager.getPath(), 
                elementConformsClass));

        // Build up the Object Path for the server profile ver 1.2.0
        // and add the elementconformstoprofile association instance
        serverProfile = buildDependencyReference(
            hostName,
            buildProfileInstanceId(SNIA_NAME, "Server", SNIA_VER_120),
            PEGASUS_CLASSNAME_PG_REGISTEREDPROFILE);
        instances.append(
            buildElementConformsToProfile(
                serverProfile,
                objManager.getPath(), 
                elementConformsClass));
        
    }
    return instances;
}