int _tmain(int argc, _TCHAR* argv[])
{
    //::DebugBreak(); 

    OutputWriter::SetVerbosityLevel(VERBOSITY_LEVEL_NORMAL); 
    OutputWriter::WriteLine(TEXT("ShadowSpawn (c) 2011 Craig Andera. [email protected]"), 
        VERBOSITY_THRESHOLD_UNLESS_SILENT); 
    OutputWriter::WriteLine(TEXT(""), VERBOSITY_THRESHOLD_UNLESS_SILENT); 

    bool bAbnormalAbort = true; 
    DWORD exitCode = 0;

    int fileCount = 0; 
    LONGLONG byteCount = 0; 
    int directoryCount = 0; 
    int skipCount = 0; 
    SYSTEMTIME startTime;
    try
    {
        COptions options = COptions::Parse(argc, argv); 

        if (options.get_Debug())
        {
            ::DebugBreak(); 
        }

        OutputWriter::SetVerbosityLevel((VERBOSITY_LEVEL) options.get_VerbosityLevel()); 

		for (int i = 0; i < argc; ++i)
		{
			CString message; 
			message.AppendFormat(TEXT("Argument %d: %s"), i, argv[i]);
			OutputWriter::WriteLine(message, VERBOSITY_THRESHOLD_IF_VERBOSE);
		}

        if (!Utilities::DirectoryExists(options.get_Source()))
        {
            CString message;
            message.AppendFormat(TEXT("Source path is not an existing directory: %s"), options.get_Source());
            throw new CShadowSpawnException(message); 
        }

        OutputWriter::WriteLine(TEXT("Calling CoInitialize")); 
        CHECK_HRESULT(::CoInitialize(NULL)); 
        CHECK_HRESULT(
            ::CoInitializeSecurity(
            NULL, 
            -1, 
            NULL, 
            NULL, 
            RPC_C_AUTHN_LEVEL_PKT_PRIVACY, 
            RPC_C_IMP_LEVEL_IDENTIFY, 
            NULL, 
            EOAC_NONE, 
            NULL)); 

        ::GetSystemTime(&startTime); 
        CString startTimeString; 
        Utilities::FormatDateTime(&startTime, TEXT(" "), false, startTimeString); 

        CString message; 
        message.AppendFormat(TEXT("Shadowing %s at %s"), 
            options.get_Source(), 
            options.get_Device()); 
        OutputWriter::WriteLine(message, VERBOSITY_THRESHOLD_NORMAL); 

		GUID systemProviderId = GetSystemProviderID();

        OutputWriter::WriteLine(TEXT("Calling CreateVssBackupComponents")); 
        CHECK_HRESULT(::CreateVssBackupComponents(&pBackupComponents)); 
		
		OutputWriter::WriteLine(TEXT("Calling InitializeForBackup")); 
        CHECK_HRESULT(pBackupComponents->InitializeForBackup()); 

        CComPtr<IVssAsync> pWriterMetadataStatus; 

        OutputWriter::WriteLine(TEXT("Calling GatherWriterMetadata")); 
        CHECK_HRESULT(pBackupComponents->GatherWriterMetadata(&pWriterMetadataStatus)); 

        OutputWriter::WriteLine(TEXT("Waiting for call to GatherWriterMetadata to finish...")); 
        CHECK_HRESULT(pWriterMetadataStatus->Wait()); 

        HRESULT hrGatherStatus; 
        OutputWriter::WriteLine(TEXT("Calling QueryStatus for GatherWriterMetadata")); 
        CHECK_HRESULT(pWriterMetadataStatus->QueryStatus(&hrGatherStatus, NULL)); 

        if (hrGatherStatus == VSS_S_ASYNC_CANCELLED)
        {
            throw new CShadowSpawnException(L"GatherWriterMetadata was cancelled."); 
        }

		OutputWriter::WriteLine(TEXT("Call to GatherWriterMetadata finished.")); 


        OutputWriter::WriteLine(TEXT("Calling GetWriterMetadataCount")); 

        vector<CWriter> writers;

        UINT cWriters; 
        CHECK_HRESULT(pBackupComponents->GetWriterMetadataCount(&cWriters)); 

        for (UINT iWriter = 0; iWriter < cWriters; ++iWriter)
        {
            CWriter writer; 
            CComPtr<IVssExamineWriterMetadata> pExamineWriterMetadata; 
            GUID id; 
            OutputWriter::WriteLine(TEXT("Calling GetWriterMetadata")); 
            CHECK_HRESULT(pBackupComponents->GetWriterMetadata(iWriter, &id, &pExamineWriterMetadata)); 
            GUID idInstance; 
            GUID idWriter; 
            BSTR bstrWriterName;
            VSS_USAGE_TYPE usage; 
            VSS_SOURCE_TYPE source; 
            CHECK_HRESULT(pExamineWriterMetadata->GetIdentity(&idInstance, &idWriter, &bstrWriterName, &usage, &source)); 

            writer.set_InstanceId(idInstance); 
            writer.set_Name(bstrWriterName); 
            writer.set_WriterId(idWriter); 

            CComBSTR writerName(bstrWriterName); 
            CString message; 
            message.AppendFormat(TEXT("Writer %d named %s"), iWriter, (LPCTSTR) writerName); 
            OutputWriter::WriteLine(message); 

            UINT cIncludeFiles;
            UINT cExcludeFiles; 
            UINT cComponents; 
            CHECK_HRESULT(pExamineWriterMetadata->GetFileCounts(&cIncludeFiles, &cExcludeFiles, &cComponents)); 

            message.Empty(); 
            message.AppendFormat(TEXT("Writer has %d components"), cComponents); 
            OutputWriter::WriteLine(message); 

            for (UINT iComponent = 0; iComponent < cComponents; ++iComponent)
            {
                CWriterComponent component; 

                CComPtr<IVssWMComponent> pComponent; 
                CHECK_HRESULT(pExamineWriterMetadata->GetComponent(iComponent, &pComponent)); 

                PVSSCOMPONENTINFO pComponentInfo; 
                CHECK_HRESULT(pComponent->GetComponentInfo(&pComponentInfo)); 

                CString message; 
                message.AppendFormat(TEXT("Component %d is named %s, has a path of %s, and is %sselectable for backup. %d files, %d databases, %d log files."), 
                    iComponent,
                    pComponentInfo->bstrComponentName, 
                    pComponentInfo->bstrLogicalPath, 
                    pComponentInfo->bSelectable ? TEXT("") : TEXT("not "), 
                    pComponentInfo->cFileCount, 
                    pComponentInfo->cDatabases,
                    pComponentInfo->cLogFiles); 
                OutputWriter::WriteLine(message); 

                component.set_LogicalPath(pComponentInfo->bstrLogicalPath); 
                component.set_SelectableForBackup(pComponentInfo->bSelectable); 
                component.set_Writer(iWriter); 
                component.set_Name(pComponentInfo->bstrComponentName);
                component.set_Type(pComponentInfo->type);

                for (UINT iFile = 0; iFile < pComponentInfo->cFileCount; ++iFile)
                {
                    CComPtr<IVssWMFiledesc> pFileDesc; 
                    CHECK_HRESULT(pComponent->GetFile(iFile, &pFileDesc)); 

                    CComBSTR bstrPath; 
                    CHECK_HRESULT(pFileDesc->GetPath(&bstrPath)); 

                    CComBSTR bstrFileSpec; 
                    CHECK_HRESULT(pFileDesc->GetFilespec(&bstrFileSpec)); 

                    CString message; 
                    message.AppendFormat(TEXT("File %d has path %s\\%s"), iFile, bstrPath, bstrFileSpec); 
                    OutputWriter::WriteLine(message); 
                }

                for (UINT iDatabase = 0; iDatabase < pComponentInfo->cDatabases; ++iDatabase)
                {
                    CComPtr<IVssWMFiledesc> pFileDesc; 
                    CHECK_HRESULT(pComponent->GetDatabaseFile(iDatabase, &pFileDesc)); 

                    CComBSTR bstrPath; 
                    CHECK_HRESULT(pFileDesc->GetPath(&bstrPath)); 

                    CComBSTR bstrFileSpec; 
                    CHECK_HRESULT(pFileDesc->GetFilespec(&bstrFileSpec)); 

                    CString message; 
                    message.AppendFormat(TEXT("Database file %d has path %s\\%s"), iDatabase, bstrPath, bstrFileSpec); 
                    OutputWriter::WriteLine(message); 
                }

                for (UINT iDatabaseLogFile = 0; iDatabaseLogFile < pComponentInfo->cLogFiles; ++iDatabaseLogFile)
                {
                    CComPtr<IVssWMFiledesc> pFileDesc; 
                    CHECK_HRESULT(pComponent->GetDatabaseLogFile(iDatabaseLogFile, &pFileDesc)); 

                    CComBSTR bstrPath; 
                    CHECK_HRESULT(pFileDesc->GetPath(&bstrPath)); 

                    CComBSTR bstrFileSpec; 
                    CHECK_HRESULT(pFileDesc->GetFilespec(&bstrFileSpec)); 

                    CString message; 
                    message.AppendFormat(TEXT("Database log file %d has path %s\\%s"), iDatabaseLogFile, bstrPath, bstrFileSpec); 
                    OutputWriter::WriteLine(message); 
                }

                CHECK_HRESULT(pComponent->FreeComponentInfo(pComponentInfo)); 

                writer.get_Components().push_back(component); 

            }

            writer.ComputeComponentTree(); 

            for (unsigned int iComponent = 0; iComponent < writer.get_Components().size(); ++iComponent)
            {
                CWriterComponent& component = writer.get_Components()[iComponent]; 
                CString message; 
                message.AppendFormat(TEXT("Component %d has name %s, path %s, is %sselectable for backup, and has parent %s"), 
                    iComponent, 
                    component.get_Name(), 
                    component.get_LogicalPath(), 
                    component.get_SelectableForBackup() ? TEXT("") : TEXT("not "), 
                    component.get_Parent() == NULL ? TEXT("(no parent)") : component.get_Parent()->get_Name()); 
                OutputWriter::WriteLine(message); 
            }

            writers.push_back(writer); 
        }

        OutputWriter::WriteLine(TEXT("Calling StartSnapshotSet")); 
        CHECK_HRESULT(pBackupComponents->StartSnapshotSet(&snapshotSetId));

        OutputWriter::WriteLine(TEXT("Calling GetVolumePathName")); 
        WCHAR wszVolumePathName[MAX_PATH]; 
        BOOL bWorked = ::GetVolumePathName(options.get_Source(), wszVolumePathName, MAX_PATH); 

        if (!bWorked)
        {
            DWORD error = ::GetLastError(); 
            CString errorMessage; 
            Utilities::FormatErrorMessage(error, errorMessage); 
            CString message; 
            message.AppendFormat(TEXT("There was an error retrieving the volume name from the path. Path: %s Error: %s"), 
                options.get_Source(), errorMessage); 
            throw new CShadowSpawnException(message.GetString()); 
        }

		
        OutputWriter::WriteLine(TEXT("Calling AddToSnapshotSet")); 
        GUID snapshotId; 
        CHECK_HRESULT(pBackupComponents->AddToSnapshotSet(wszVolumePathName, systemProviderId, &snapshotId)); 

        for (unsigned int iWriter = 0; iWriter < writers.size(); ++iWriter)
        {
            CWriter writer = writers[iWriter];

            CString message; 
            message.AppendFormat(TEXT("Adding components to snapshot set for writer %s"), writer.get_Name()); 
            OutputWriter::WriteLine(message); 
            for (unsigned int iComponent = 0; iComponent < writer.get_Components().size(); ++iComponent)
            {
                CWriterComponent component = writer.get_Components()[iComponent];

                if (ShouldAddComponent(component))
                {
                    CString message; 
                    message.AppendFormat(TEXT("Adding component %s (%s) from writer %s"), 
                        component.get_Name(), 
                        component.get_LogicalPath(), 
                        writer.get_Name()); 
                    OutputWriter::WriteLine(message); 
                    CHECK_HRESULT(pBackupComponents->AddComponent(
                        writer.get_InstanceId(), 
                        writer.get_WriterId(),
                        component.get_Type(), 
                        component.get_LogicalPath(), 
                        component.get_Name()
                        ));
                }
                else
                {
                    CString message; 
                    message.AppendFormat(TEXT("Not adding component %s from writer %s."), 
                        component.get_Name(), writer.get_Name()); 
                    OutputWriter::WriteLine(message); 
                }
            }
        }

        OutputWriter::WriteLine(TEXT("Calling SetBackupState")); 
        CHECK_HRESULT(pBackupComponents->SetBackupState(TRUE, FALSE, options.get_BackupType(), FALSE)); 

        OutputWriter::WriteLine(TEXT("Calling PrepareForBackup")); 
        CComPtr<IVssAsync> pPrepareForBackupResults; 
        CHECK_HRESULT(pBackupComponents->PrepareForBackup(&pPrepareForBackupResults)); 

        OutputWriter::WriteLine(TEXT("Waiting for call to PrepareForBackup to finish...")); 
        CHECK_HRESULT(pPrepareForBackupResults->Wait()); 

        HRESULT hrPrepareForBackupResults; 
        CHECK_HRESULT(pPrepareForBackupResults->QueryStatus(&hrPrepareForBackupResults, NULL)); 

        if (hrPrepareForBackupResults != VSS_S_ASYNC_FINISHED)
        {
            throw new CShadowSpawnException(TEXT("Prepare for backup failed.")); 
        }

        OutputWriter::WriteLine(TEXT("Call to PrepareForBackup finished.")); 
		
        SYSTEMTIME snapshotTime; 
        ::GetSystemTime(&snapshotTime); 

        bWorked = ::SetConsoleCtrlHandler(CtrlHandler, TRUE); 

        if (!bWorked)
        {
            OutputWriter::WriteLine(TEXT("Unable to set control handler. Ctrl-C and Ctrl-Break may have undesirable results."), 
                VERBOSITY_THRESHOLD_NORMAL);
        }

        if (!options.get_Simulate())
        {
            OutputWriter::WriteLine(TEXT("Calling DoSnapshotSet")); 
            CComPtr<IVssAsync> pDoSnapshotSetResults;
            CHECK_HRESULT(pBackupComponents->DoSnapshotSet(&pDoSnapshotSetResults)); 

            OutputWriter::WriteLine(TEXT("Waiting for call to DoSnapshotSet to finish...")); 
		   
            CHECK_HRESULT(pDoSnapshotSetResults->Wait());

            bSnapshotCreated = true; 

             HRESULT hrDoSnapshotSetResults; 
            CHECK_HRESULT(pDoSnapshotSetResults->QueryStatus(&hrDoSnapshotSetResults, NULL)); 

            if (hrDoSnapshotSetResults != VSS_S_ASYNC_FINISHED)
            {
                throw new CShadowSpawnException(L"DoSnapshotSet failed."); 
            }

	        OutputWriter::WriteLine(TEXT("Call to DoSnapshotSet finished.")); 

            OutputWriter::WriteLine(TEXT("Calling GetSnapshotProperties")); 
            VSS_SNAPSHOT_PROP snapshotProperties; 
            CHECK_HRESULT(pBackupComponents->GetSnapshotProperties(snapshotId, &snapshotProperties));

            OutputWriter::WriteLine(TEXT("Calling CalculateSourcePath")); 
            // TODO: We'll eventually have to deal with mount points
            CString wszSource;
            CalculateSourcePath(
                snapshotProperties.m_pwszSnapshotDeviceObject, 
                options.get_Source(),
                wszVolumePathName, 
                wszSource
                );

            OutputWriter::WriteLine(TEXT("Calling DefineDosDevice to mount device.")); 
            if (0 == wszSource.Find(TEXT("\\\\?\\GLOBALROOT")))
            {
                wszSource = wszSource.Mid(_tcslen(TEXT("\\\\?\\GLOBALROOT")));
            }
            bWorked = DefineDosDevice(DDD_RAW_TARGET_PATH, options.get_Device(), wszSource); 
            if (!bWorked)
            {
                DWORD error = ::GetLastError(); 
                CString errorMessage; 
                Utilities::FormatErrorMessage(error, errorMessage); 
                CString message; 
                message.AppendFormat(TEXT("There was an error calling DefineDosDevice when mounting a device. Error: %s"), errorMessage); 
                throw new CShadowSpawnException(message.GetString()); 
            }
            mountedDevice = options.get_Device();

            STARTUPINFO startUpInfo;
            memset(&startUpInfo, 0, sizeof(startUpInfo));
            startUpInfo.cb = sizeof(startUpInfo);

            PROCESS_INFORMATION processInformation;
            size_t commandLength = options.get_Command().size();
            wchar_t* copyCommand = (wchar_t*)_alloca((commandLength+1)*sizeof(wchar_t));
            options.get_Command().copy(copyCommand, commandLength);
            copyCommand[commandLength] = L'\0';

            message.Format(TEXT("Launching command: %s"), options.get_Command().c_str());
            OutputWriter::WriteLine(message, VERBOSITY_THRESHOLD_NORMAL); 
            bWorked = CreateProcess(NULL, copyCommand, NULL, NULL, FALSE, 0, NULL, 
                                    NULL, &startUpInfo, &processInformation);
            if (!bWorked)
            {
                DWORD error = ::GetLastError(); 
                CString errorMessage; 
                Utilities::FormatErrorMessage(error, errorMessage); 
                CString message; 
                message.AppendFormat(TEXT("There was an error calling CreateProcess. Process: %s Error: %s"), 
                    options.get_Command().c_str(), errorMessage); 
                throw new CShadowSpawnException(message.GetString()); 
            }

            WaitForSingleObject(processInformation.hProcess, INFINITE);

            bWorked = GetExitCodeProcess(processInformation.hProcess, &exitCode);
            if (!bWorked)
            {
                DWORD error = ::GetLastError(); 
                CString errorMessage; 
                Utilities::FormatErrorMessage(error, errorMessage); 
                CString message; 
                message.AppendFormat(TEXT("There was an error calling GetExitCodeProcess. Error: %s"), errorMessage); 
                throw new CShadowSpawnException(message.GetString()); 
            }

            CloseHandle(processInformation.hThread);
            CloseHandle(processInformation.hProcess);

            message.Format(TEXT("Launched command finished with exit code: %d."), exitCode);
            OutputWriter::WriteLine(message, VERBOSITY_THRESHOLD_NORMAL); 

            OutputWriter::WriteLine(TEXT("Calling DefineDosDevice to remove device.")); 
            bWorked = DefineDosDevice(DDD_REMOVE_DEFINITION, options.get_Device(), NULL); 
            if (!bWorked)
            {
                DWORD error = ::GetLastError(); 
                CString errorMessage; 
                Utilities::FormatErrorMessage(error, errorMessage); 
                CString message; 
                message.AppendFormat(TEXT("There was an error calling DefineDosDevice. Error: %s"), errorMessage); 
                throw new CShadowSpawnException(message.GetString()); 
            }
            mountedDevice.Empty();

            OutputWriter::WriteLine(TEXT("Calling BackupComplete")); 
            CComPtr<IVssAsync> pBackupCompleteResults; 
            CHECK_HRESULT(pBackupComponents->BackupComplete(&pBackupCompleteResults)); 

            OutputWriter::WriteLine(TEXT("Waiting for call to BackupComplete to finish...")); 
			CHECK_HRESULT(pBackupCompleteResults->Wait());

            HRESULT hrBackupCompleteResults; 
            CHECK_HRESULT(pBackupCompleteResults->QueryStatus(&hrBackupCompleteResults, NULL)); 

            if (hrBackupCompleteResults != VSS_S_ASYNC_FINISHED)
            {
                throw new CShadowSpawnException(TEXT("Completion of backup failed.")); 
            }

            OutputWriter::WriteLine(TEXT("Call to BackupComplete finished.")); 

            bAbnormalAbort = false; 
        }
    }
    catch (CComException* e)
    {
        Cleanup(bAbnormalAbort, bSnapshotCreated, mountedDevice, pBackupComponents, snapshotSetId);
        CString message; 
        CString file; 
        e->get_File(file); 
        message.Format(TEXT("There was a COM failure 0x%x - %s (%d)"), 
            e->get_Hresult(), file, e->get_Line()); 
        OutputWriter::WriteLine(message, VERBOSITY_THRESHOLD_UNLESS_SILENT); 
        return 1; 
    }
    catch (CShadowSpawnException* e)
    {
        Cleanup(bAbnormalAbort, bSnapshotCreated, mountedDevice, pBackupComponents, snapshotSetId);
        OutputWriter::WriteLine(e->get_Message(), VERBOSITY_THRESHOLD_UNLESS_SILENT); 
        return 1; 
    }
    catch (CParseOptionsException* e)
    {
        Cleanup(bAbnormalAbort, bSnapshotCreated, mountedDevice, pBackupComponents, snapshotSetId);
        CString message; 
        message.AppendFormat(TEXT("Error: %s\n"), e->get_Message()); 
        OutputWriter::WriteLine(message, VERBOSITY_THRESHOLD_UNLESS_SILENT);
        OutputWriter::WriteLine(COptions::get_Usage(), VERBOSITY_THRESHOLD_UNLESS_SILENT); 
        return 2; 
    }

    Cleanup(false, bSnapshotCreated, mountedDevice, pBackupComponents, snapshotSetId);
    OutputWriter::WriteLine(TEXT("Shadowing successfully completed."), VERBOSITY_THRESHOLD_NORMAL); 
    if (exitCode != 0)
    {
        return (0x8000 | exitCode);
    }

    return 0;
}