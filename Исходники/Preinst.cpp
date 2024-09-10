int PASCAL WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPTSTR lpCmdLine,int nCmdShow)
{
    if (!InitializeOptions(lpCmdLine))
    {
        if (!OptionSilent)
        {
            MessageBox(NULL, "Please specify the correct parameters:\r\n" \
                       "/path <Full path to the INF>\r\n" \
                       "/path:relative <Relative path to the INF from the current directory>\r\n" \
                       "/ddinstall <DDInstall section name to be processed>\r\n" \
                       "/os <Expected OS version in the form of x.y where x is MajorVersion, y is Minor version, ie 5.0 for Windows 2000>\r\n" \
                       "/buildnumber <Expected OS build number, ie 2195 for Windows 2000>\r\n" \
                       "/sp <Expected OS service pack number>\r\n",
                       "Pre-Installer",
                       MB_OK);

        }

        return ERR_FAIL;
    }

    if ((OptionOsVersionCheck) || (OptionOsBuildNumberCheck) || (OptionOsServicePackCheck))
    {
        OSVERSIONINFO OsVersionInfo;
        OsVersionInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

        if (GetVersionEx(&OsVersionInfo))
        {
            if (OptionOsVersionCheck)
            {
                CHAR Version[32];

                sprintf(Version, "%d.%d", OsVersionInfo.dwMajorVersion, OsVersionInfo.dwMinorVersion);

                if (_stricmp(Version, ExpectedOsVersion))
                {
                    if (!OptionSilent)
                    {
                        CHAR ErrorMsg[256];
                        sprintf(ErrorMsg, "OS version %s doesn't match the expected %s", Version, ExpectedOsVersion);

                        MessageBox(NULL, ErrorMsg, "Pre-Installer", MB_OK);
                    }

                    return ERR_FAIL;
                }
            }

            if (OptionOsBuildNumberCheck)
            {
                if (OsVersionInfo.dwBuildNumber != ExpectedOsBuildNumber)
                {
                    if (!OptionSilent)
                    {
                        CHAR ErrorMsg[256];
                        sprintf(ErrorMsg, "OS build number %d doesn't match the expected %d", OsVersionInfo.dwBuildNumber, ExpectedOsBuildNumber);

                        MessageBox(NULL, ErrorMsg, "Pre-Installer", MB_OK);
                    }

                    return ERR_FAIL;
                }
            }

            if (OptionOsServicePackCheck)
            {
                CHAR ServicePack[32];

                sprintf(ServicePack, "Service Pack %d", ExpectedOsServicePack);

                if (_stricmp(OsVersionInfo.szCSDVersion, ServicePack))
                {
                    if (!OptionSilent)
                    {
                        CHAR ErrorMsg[256];
                        sprintf(ErrorMsg, "OS %s doesn't match the expected %s", OsVersionInfo.szCSDVersion, ServicePack);

                        MessageBox(NULL, ErrorMsg, "Pre-Installer", MB_OK);
                    }

                    return ERR_FAIL;
                }
            }
        }
        else
        {
            return ERR_FAIL;
        }
    }

    HINF InfHandle = SetupOpenInfFile(InfPath, NULL, INF_STYLE_WIN4 , NULL);	// Get INF Handle

    if (InfHandle != INVALID_HANDLE_VALUE)
    {
        HSPFILEQ QueueHandle = SetupOpenFileQueue();

        if (QueueHandle != INVALID_HANDLE_VALUE)
        {
            SetupInstallFilesFromInfSection(InfHandle, NULL, QueueHandle, DDInstallSection, NULL, SP_COPY_FORCE_NEWER);
            //Copies the files

            PVOID Context = SetupInitDefaultQueueCallback(NULL);

            if (Context)
            {
                SetupCommitFileQueue(NULL, QueueHandle, FileCallback, Context);

                SetupTermDefaultQueueCallback(Context);
            }

            SetupCloseFileQueue(QueueHandle);
        }

        // Do not do the following as we do not want to install the drivers yet. When the device is turned on,
        // Windows PnP will take care of the rest of the installation process.
#if 0
        CHAR DDInstallServicesSection[MAX_PATH];

        strcpy(DDInstallServicesSection, DDInstallSection);
        strcat(DDInstallServicesSection, ".Services");

        SetupInstallServicesFromInfSection(InfHandle, DDInstallServicesSection, SPSVCINST_TAGTOFRONT);

        HKEY RegKey = SetupDiOpenClassRegKey((LPGUID)&CLSID_MEDIA, KEY_ALL_ACCESS);

        if (RegKey != INVALID_HANDLE_VALUE)
        {
            SetupInstallFromInfSection(NULL, InfHandle, DDInstallSection, SPINST_REGISTRY, RegKey, NULL, NULL,
                                       NULL, NULL, NULL, NULL);		// Does the AddReg, Del Reg Stuff

            RegCloseKey(RegKey);
        }
#endif // 0

        SetupCloseInfFile(InfHandle);
    }

    if (SetupCopyOEMInf(InfPath, NULL, SPOST_PATH, NULL, NULL ,0, NULL, NULL))
    {
        return SUCCESS;
    }
    else
    {
        DWORD err = GetLastError();

        return ERR_FAIL;
    }
}