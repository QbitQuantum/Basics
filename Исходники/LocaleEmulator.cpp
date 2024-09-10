NTSTATUS LeGlobalData::Initialize()
{
    BOOL            IsLoader;
    PLEPEB          LePeb;
    PLDR_MODULE     Ntdll;
    PPEB_BASE       Peb;
    NTSTATUS        Status;
    NLSTABLEINFO    NlsTableInfo;
    UNICODE_STRING  SystemDirectory, NlsFileName, OemNlsFileName, LangFileName;
    PKEY_VALUE_PARTIAL_INFORMATION IndexValue;

    IsLoader = IsLeLoader();

    Wow64 = Ps::IsWow64Process();
    Ntdll = GetNtdllLdrModule();

    LOOP_ONCE
    {
        LePeb = OpenOrCreateLePeb();
        if (LePeb == nullptr)
        {
            ULONG_PTR       DefaultACPLength, DefaultLCIDLength, DefaultOEMCPLength;
            WCHAR           DefaultACP[0x20], DefaultOEMCP[0x20], DefaultLCID[0x20];
            PVOID           ReloadedNtdll;
            PUNICODE_STRING FullDllName;

            LePeb = GetLePeb();

            InitDefaultLeb(&LePeb->Leb);

            FullDllName = &FindLdrModuleByHandle(&__ImageBase)->FullDllName;
            CopyMemory(LePeb->LeDllFullPath, FullDllName->Buffer, FullDllName->Length + sizeof(WCHAR));

            Status = LoadPeImage(Ntdll->FullDllName.Buffer, &ReloadedNtdll, nullptr, LOAD_PE_IGNORE_RELOC);
            if (NT_SUCCESS(Status))
            {
                PVOID LdrLoadDllAddress;

                LdrLoadDllAddress = LookupExportTable(ReloadedNtdll, NTDLL_LdrLoadDll);
                LePeb->LdrLoadDllAddress = PtrAdd(LdrLoadDllAddress, PtrOffset(Ntdll->DllBase, ReloadedNtdll));
                CopyMemory(LePeb->LdrLoadDllBackup, LdrLoadDllAddress, LDR_LOAD_DLL_BACKUP_SIZE);
                LePeb->LdrLoadDllBackupSize = LDR_LOAD_DLL_BACKUP_SIZE;

                UnloadPeImage(ReloadedNtdll);
            }

            DefaultACPLength    = (swprintf(DefaultACP, L"%d", LePeb->Leb.AnsiCodePage) + 1) * sizeof(WCHAR);
            DefaultOEMCPLength  = (swprintf(DefaultOEMCP, L"%d", LePeb->Leb.OemCodePage) + 1) * sizeof(WCHAR);
            DefaultLCIDLength   = (swprintf(DefaultLCID, L"%d", LePeb->Leb.LocaleID) + 1) * sizeof(WCHAR);

            REGISTRY_REDIRECTION_ENTRY64 *Entry, Entries[] =
            {
                {
                    { (ULONG64)HKEY_LOCAL_MACHINE, USTR64(REGPATH_CODEPAGE), USTR64(REGKEY_ACP), REG_SZ, },
                    { (ULONG64)HKEY_LOCAL_MACHINE, USTR64(REGPATH_CODEPAGE), USTR64(REGKEY_ACP), REG_SZ, DefaultACP, DefaultACPLength },
                },
                {
                    { (ULONG64)HKEY_LOCAL_MACHINE, USTR64(REGPATH_CODEPAGE), USTR64(REGKEY_OEMCP), REG_SZ, },
                    { (ULONG64)HKEY_LOCAL_MACHINE, USTR64(REGPATH_CODEPAGE), USTR64(REGKEY_OEMCP), REG_SZ, DefaultOEMCP, DefaultOEMCPLength },
                },
                {
                    { (ULONG64)HKEY_LOCAL_MACHINE, USTR64(REGPATH_LANGUAGE), USTR64(REGKEY_DEFAULT_LANGUAGE), REG_SZ, },
                    { (ULONG64)HKEY_LOCAL_MACHINE, USTR64(REGPATH_LANGUAGE), USTR64(REGKEY_DEFAULT_LANGUAGE), REG_SZ, DefaultLCID, DefaultLCIDLength },
                },
            };

            Status = this->InitRegistryRedirection(Entries, countof(Entries), nullptr);
        }
        else
        {
            *GetLePeb() = *LePeb;
            Status = this->InitRegistryRedirection(LePeb->Leb.RegistryReplacement, LePeb->Leb.NumberOfRegistryRedirectionEntries, &LePeb->Leb);

            NtClose(LePeb->Section);
            CloseLePeb(LePeb);
        }

        if (IsLoader)
            break;

        Status = this->TextMetricCache.Initialize();
        FAIL_RETURN(Status);

        PVOID           NlsBaseAddress;
        LCID            DefaultLocaleID;
        LARGE_INTEGER   DefaultCasingTableSize;

        Status = NtInitializeNlsFiles(&NlsBaseAddress, &DefaultLocaleID, &DefaultCasingTableSize);
        FAIL_RETURN(Status);

        this->GetLePeb()->OriginalLocaleID = DefaultLocaleID;

        NtUnmapViewOfSection(CurrentProcess, NlsBaseAddress);

        WriteLog(L"init leb %s", GetLePeb()->LeDllFullPath);

        SystemDirectory = Ntdll->FullDllName;
        SystemDirectory.Length -= Ntdll->BaseDllName.Length;

        Status = RtlDuplicateUnicodeString(RTL_DUPSTR_ADD_NULL, &SystemDirectory, &this->SystemDirectory);
        FAIL_RETURN(Status);

        RtlInitEmptyString(&NlsFileName, nullptr, 0);
        RtlInitEmptyString(&OemNlsFileName, nullptr, 0);
        RtlInitEmptyString(&LangFileName, nullptr, 0);

        SCOPE_EXIT
        {
            RtlFreeUnicodeString(&NlsFileName);
            RtlFreeUnicodeString(&OemNlsFileName);
            RtlFreeUnicodeString(&LangFileName);
        }
        SCOPE_EXIT_END;

        Status = GetNlsFile(&NlsFileName, GetLeb()->AnsiCodePage, REGPATH_CODEPAGE);
        FAIL_RETURN(Status);

        Status = GetNlsFile(&OemNlsFileName, GetLeb()->OemCodePage, REGPATH_CODEPAGE);
        FAIL_RETURN(Status);

        Status = GetLangFile(&LangFileName, GetLeb()->LocaleID, REGPATH_LANGUAGE);
        FAIL_RETURN(Status);

        NtFileMemory AnsiFile, OemFile, LangFile;

        Status = ReadFileInSystemDirectory(AnsiFile, &NlsFileName);
        FAIL_RETURN(Status);

        Status = ReadFileInSystemDirectory(OemFile, &OemNlsFileName);
        FAIL_RETURN(Status);

        Status = ReadFileInSystemDirectory(LangFile, &LangFileName);
        FAIL_RETURN(Status);

        AnsiCodePageOffset      = 0;
        OemCodePageOffset       = ROUND_UP(AnsiFile.GetSize32(), 16);
        UnicodeCaseTableOffset  = OemCodePageOffset + ROUND_UP(OemFile.GetSize32(), 16);

        Status = AllocVirtualMemory(&CodePageMapView, UnicodeCaseTableOffset + LangFile.GetSize32(), PAGE_READWRITE, MEM_COMMIT | MEM_TOP_DOWN);
        FAIL_RETURN(Status);

        CopyMemory(PtrAdd(CodePageMapView, AnsiCodePageOffset),     AnsiFile.GetBuffer(),   AnsiFile.GetSize32());
        CopyMemory(PtrAdd(CodePageMapView, OemCodePageOffset),      OemFile.GetBuffer(),    OemFile.GetSize32());
        CopyMemory(PtrAdd(CodePageMapView, UnicodeCaseTableOffset), LangFile.GetBuffer(),   LangFile.GetSize32());

        ProtectVirtualMemory(CodePageMapView, UnicodeCaseTableOffset + LangFile.GetSize32(), PAGE_READONLY);

        RtlInitNlsTables(
            (PUSHORT)PtrAdd(CodePageMapView, AnsiCodePageOffset),
            (PUSHORT)PtrAdd(CodePageMapView, OemCodePageOffset),
            (PUSHORT)PtrAdd(CodePageMapView, UnicodeCaseTableOffset),
            &NlsTableInfo
        );

        RtlResetRtlTranslations(&NlsTableInfo);

        WriteLog(L"reset nls");

        Peb = CurrentPeb();

        Peb->AnsiCodePageData       = (PUSHORT)PtrAdd(CodePageMapView, AnsiCodePageOffset);
        Peb->OemCodePageData        = (PUSHORT)PtrAdd(CodePageMapView, OemCodePageOffset);
        Peb->UnicodeCaseTableData   = (PUSHORT)PtrAdd(CodePageMapView, UnicodeCaseTableOffset);

        // LdrInitShimEngineDynamic(&__ImageBase);

        LdrRegisterDllNotification(0,
            [] (ULONG NotificationReason, PCLDR_DLL_NOTIFICATION_DATA NotificationData, PVOID Context)
            {
                return ((PLeGlobalData)Context)->DllNotification(NotificationReason, NotificationData);
            },
            this,
            &DllNotificationCookie
        );
    }

    Status = InstallHookPort();
    WriteLog(L"inst hp: %08X", Status);
    FAIL_RETURN(Status);

    HookNtdllRoutines(Ntdll->DllBase);

    WriteLog(L"hook ntdll");

    if (IsLoader)
        return Status;

    PLDR_MODULE Kernel32Ldr;

    Kernel32Ldr = GetKernel32Ldr();
    if (Kernel32Ldr != nullptr)
    {
        Kernel32Ldr->EntryPoint = DelayInitDllEntry;
        // HookKernel32Routines(Kernel32Ldr->DllBase);
    }

    WriteLog(L"init %p", Status);

    return Status;
}