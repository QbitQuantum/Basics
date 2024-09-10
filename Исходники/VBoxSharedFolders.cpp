int VBoxSharedFoldersAutoMount(void)
{
    uint32_t u32ClientId;
    int rc = VbglR3SharedFolderConnect(&u32ClientId);
    if (RT_FAILURE(rc))
        Log(("VBoxTray: Failed to connect to the shared folder service, error %Rrc\n", rc));
    else
    {
        uint32_t cMappings;
        VBGLR3SHAREDFOLDERMAPPING *paMappings;

        rc = VbglR3SharedFolderGetMappings(u32ClientId, true /* Only process auto-mounted folders */,
                                           &paMappings, &cMappings);
        if (RT_SUCCESS(rc))
        {
#if 0
            /* Check for a fixed/virtual auto-mount share. */
            if (VbglR3SharedFolderExists(u32ClientId, "vbsfAutoMount"))
            {
                Log(("VBoxTray: Hosts supports auto-mount root\n"));
            }
            else
            {
#endif
                Log(("VBoxTray: Got %u shared folder mappings\n", cMappings));
                for (uint32_t i = 0; i < cMappings && RT_SUCCESS(rc); i++)
                {
                    char *pszName = NULL;
                    rc = VbglR3SharedFolderGetName(u32ClientId, paMappings[i].u32Root, &pszName);
                    if (   RT_SUCCESS(rc)
                        && *pszName)
                    {
                        Log(("VBoxTray: Connecting share %u (%s) ...\n", i+1, pszName));

                        char *pszShareName;
                        if (RTStrAPrintf(&pszShareName, "\\\\vboxsrv\\%s", pszName) >= 0)
                        {
                            char chDrive = 'D'; /* Start probing whether drive D: is free to use. */
                            do
                            {
                                char szCurDrive[3];
                                RTStrPrintf(szCurDrive, sizeof(szCurDrive), "%c:", chDrive++);

                                NETRESOURCE resource;
                                RT_ZERO(resource);
                                resource.dwType = RESOURCETYPE_ANY;
                                resource.lpLocalName = TEXT(szCurDrive);
                                resource.lpRemoteName = TEXT(pszShareName);
                                /* Go straight to our network provider in order to get maximum lookup speed. */
                                resource.lpProvider = TEXT("VirtualBox Shared Folders");

                                /** @todo Figure out how to map the drives in a block (F,G,H, ...).
                                          Save the mapping for later use. */
                                DWORD dwErr = WNetAddConnection2A(&resource, NULL, NULL, 0);
                                if (dwErr == NO_ERROR)
                                {
                                    LogRel(("VBoxTray: Shared folder \"%s\" was mounted to drive \"%s\"\n", pszName, szCurDrive));
                                    break;
                                }
                                else
                                {
                                    LogRel(("VBoxTray: Mounting \"%s\" to \"%s\" resulted in dwErr = %ld\n", pszName, szCurDrive, dwErr));

                                    switch (dwErr)
                                    {
                                        /*
                                         * The local device specified by the lpLocalName member is already
                                         * connected to a network resource.  Try next drive ...
                                         */
                                        case ERROR_ALREADY_ASSIGNED:
                                            break;

                                        default:
                                            LogRel(("VBoxTray: Error while mounting shared folder \"%s\" to \"%s\", error = %ld\n",
                                                    pszName, szCurDrive, dwErr));
                                            break;
                                    }
                                }
                            } while (chDrive <= 'Z');

                            if (chDrive > 'Z')
                            {
                                LogRel(("VBoxTray: No free driver letter found to assign shared folder \"%s\", aborting\n", pszName));
                                break;
                            }

                            RTStrFree(pszShareName);
                        }
                        else
                            rc = VERR_NO_STR_MEMORY;
                        RTStrFree(pszName);
                    }
                    else
                        Log(("VBoxTray: Error while getting the shared folder name for root node = %u, rc = %Rrc\n",
                             paMappings[i].u32Root, rc));
                }
#if 0
            }
#endif
            RTMemFree(paMappings);
        }
        else
            Log(("VBoxTray: Error while getting the shared folder mappings, rc = %Rrc\n", rc));
        VbglR3SharedFolderDisconnect(u32ClientId);
    }
    return rc;
}