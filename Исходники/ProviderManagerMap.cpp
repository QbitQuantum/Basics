void ProviderManagerMap::initialize()
{
    String libExt = FileSystem::getDynamicLibraryExtension();
    // first add the default:

    ProvMgrIfcInfo defaultPMEntry;
    defaultPMEntry.path.clear();
    defaultPMEntry.ifcName = "C++Default";
    defaultPMEntry.ifcVersions.append(String("2.1.0"));
    defaultPMEntry.ifcVersions.append(String("2.2.0"));
    defaultPMEntry.ifcVersions.append(String("2.3.0"));
    defaultPMEntry.ifcVersions.append(String("2.5.0"));
    defaultPMEntry.ifcVersions.append(String("2.6.0"));
    defaultPMEntry.ifcVersions.append(String("2.9.0"));
    _pmArray.append(defaultPMEntry);

    // now check for plugins

    String dirName = ConfigManager::getInstance()->getCurrentValue(
            "providerManagerDir");
    dirName = ConfigManager::getHomedPath(dirName);

    PEG_TRACE((TRC_PROVIDERMANAGER, Tracer::LEVEL3,
        "Looking for ProviderManagers in %s.",
        (const char*)dirName.getCString()));

    // check to make sure that this ifc type is handled by one of the
    // provider managers in the directory
    String testname = String("providermanager")+libExt;
    for (Dir dir(dirName); dir.more(); dir.next())
    {
        String filename = dir.getName();
        String lowerFilename = filename;
        lowerFilename.toLower();
        if ((lowerFilename.subString(lowerFilename.size()-testname.size()) ==
                 testname) &&
            (lowerFilename !=
                 FileSystem::buildLibraryFileName("defaultprovidermanager")) &&
            (lowerFilename !=
                 FileSystem::buildLibraryFileName("pegprovidermanager")))
        {
            String fullPath = dirName + "/" + filename;
            // found a file... assume it's a ProviderManager library
            PEG_TRACE((TRC_PROVIDERMANAGER, Tracer::LEVEL4,
                "Found file %s. Checking to see if it is a ProviderManager.",
                (const char*)fullPath.getCString()));
            DynamicLibrary dl(fullPath);
            if (!dl.load())
            {
                Logger::put_l(Logger::ERROR_LOG, System::CIMSERVER,
                    Logger::SEVERE,
                    MessageLoaderParms(
                        "Server.ProviderRegistrationManager.ProviderManagerMap."
                            "LOAD_ERROR",
                        "Error loading library $0: $1.",
                        fullPath, dl.getLoadErrorMessage()));
                continue;    // to the next file
            }

            Uint32 (*get_peg_ver)() =
                (Uint32(*)()) dl.getSymbol("getPegasusVersion");

            if (get_peg_ver == 0)
            {
                Logger::put_l(Logger::ERROR_LOG, System::CIMSERVER,
                    Logger::SEVERE,
                    MessageLoaderParms(
                        "Server.ProviderRegistrationManager.ProviderManagerMap."
                            "MISSING_GET_PG_VERSION",
                        "Library $0 does not contain expected function "
                            "'getPegasusVersion'.",
                        fullPath));
                continue;
            }

            Uint32 peg_ver = get_peg_ver();
            if (peg_ver != PEGASUS_VERSION_NUMBER)
            {
                Logger::put_l(Logger::ERROR_LOG, System::CIMSERVER,
                    Logger::SEVERE,
                    MessageLoaderParms(
                        "Server.ProviderRegistrationManager.ProviderManagerMap."
                            "WRONG_VERSION",
                        "Provider Manager $0 returned Pegasus "
                            "version $1.  Expected $2.",
                        fullPath, peg_ver, PEGASUS_VERSION_NUMBER));
                continue;
            }

            const char** (*get_ifc)() = (const char**(*)()) dl.getSymbol(
                "getProviderManagerInterfaceNames");
            const char** (*get_ver)(const char *) =
                (const char**(*)(const char *)) dl.getSymbol(
                    "getProviderManagerInterfaceVersions");
            if (get_ifc == 0)
            {
                Logger::put_l(Logger::ERROR_LOG, System::CIMSERVER,
                    Logger::SEVERE,
                    MessageLoaderParms(
                        "Server.ProviderRegistrationManager.ProviderManagerMap."
                            "MISSING_GET_IFC_NAMES",
                        "Provider Manager $0 does not contain expected "
                            "function 'getProviderManagerInterfaceNames'",
                        fullPath));
                continue;    // to the next file
            }
            if (get_ver == 0)
            {
                Logger::put_l(Logger::ERROR_LOG, System::CIMSERVER,
                    Logger::SEVERE,
                    MessageLoaderParms(
                        "Server.ProviderRegistrationManager.ProviderManagerMap."
                            "MISSING_GET_IFC_VERSIONS",
                        "Provider Manager $0 does not contain expected "
                            "function 'getProviderManagerInterfaceVersions'",
                        fullPath));
                continue;    // to the next file
            }

            const char ** ifcNames = get_ifc();
            if ((ifcNames!=NULL) && (*ifcNames!=NULL))
            {
                for (int i=0; ifcNames[i]!=NULL; i++)
                {
                    const char *ifcName = ifcNames[i];

                    ProvMgrIfcInfo entry;
                    entry.path = fullPath;
                    entry.ifcName = ifcName;

                    // now get the versions
                    const char ** ifcVersions = get_ver(ifcName);
                    for (int j=0; ifcVersions[j]!=NULL; j++)
                    {
                        entry.ifcVersions.append(String(ifcVersions[j]));
                        PEG_TRACE((TRC_PROVIDERMANAGER, Tracer::LEVEL3,
                            "Adding Provider type %s version %s "
                            "handled by ProviderManager %s",
                             ifcName,ifcVersions[j],
                             (const char*)fullPath.getCString()));
                    }
                    _pmArray.append(entry);
                }
            }
        }
    }
    _bInitialized = true;
}