void SuDeleteGarbageInfsInner()
{
    char *base_key_name = "DRIVERS\\DriverDatabase\\DriverPackages";
    TOKEN_LIST *keys;
    HINSTANCE hSetupApiDll = NULL;
    BOOL (WINAPI *_SetupUninstallOEMInfA)(PCSTR, DWORD, PVOID) = NULL;

    if (MsIsWindows10() == false)
    {
        return;
    }

    hSetupApiDll = LoadLibraryA("setupapi.dll");
    if (hSetupApiDll == NULL)
    {
        return;
    }

    _SetupUninstallOEMInfA =
        (UINT (__stdcall *)(PCSTR,DWORD,PVOID))
        GetProcAddress(hSetupApiDll, "SetupUninstallOEMInfA");

    if (_SetupUninstallOEMInfA != NULL)
    {
        keys = MsRegEnumKeyEx2(REG_LOCAL_MACHINE, base_key_name, false, true);

        if (keys != NULL)
        {
            char full_key[MAX_PATH];
            UINT i;

            for (i = 0; i < keys->NumTokens; i++)
            {
                char *oem_name, *inf_name, *provider;

                Format(full_key, sizeof(full_key), "%s\\%s", base_key_name, keys->Token[i]);

                oem_name = MsRegReadStrEx2(REG_LOCAL_MACHINE, full_key, "", false, true);
                inf_name = MsRegReadStrEx2(REG_LOCAL_MACHINE, full_key, "InfName", false, true);
                provider = MsRegReadStrEx2(REG_LOCAL_MACHINE, full_key, "Provider", false, true);

                if (IsEmptyStr(oem_name) == false && IsEmptyStr(inf_name) == false)
                {
                    if (StartWith(oem_name, "oem"))
                    {
                        if (StartWith(inf_name, "selow"))
                        {
                            if (InStr(provider, "softether"))
                            {
                                Debug("Delete OEM INF %s (%s): %u\n",
                                      oem_name, inf_name,
                                      _SetupUninstallOEMInfA(oem_name, 0x00000001, NULL));
                            }
                        }
                    }
                }

                Free(oem_name);
                Free(inf_name);
                Free(provider);
            }

            FreeToken(keys);
        }
    }

    if (hSetupApiDll != NULL)
    {
        FreeLibrary(hSetupApiDll);
    }
}