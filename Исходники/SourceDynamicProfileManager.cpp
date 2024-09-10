    //
    // Saves the profile to the WININET cache
    //
    uint SourceDynamicProfileManager::SaveToProfileCache()
    {
        AssertMsg(CONFIG_FLAG(WininetProfileCache), "Profile caching should be enabled for us to get here");
        Assert(startupFunctions);

        uint bytesWritten = 0;
#ifdef ENABLE_WININET_PROFILE_DATA_CACHE
        //TODO: Add some diffing logic to not write unless necessary
        IStream* writeStream;
        HRESULT hr = profileDataCache->GetWriteDataStream(&writeStream);
        if(FAILED(hr))
        {
            return 0;
        }
        Assert(writeStream != nullptr);
        // stream writer owns the stream and will close it on destruction
        SimpleStreamWriter streamWriter(writeStream);

        DWORD jscriptMajorVersion;
        DWORD jscriptMinorVersion;
        if(FAILED(AutoSystemInfo::GetJscriptFileVersion(&jscriptMajorVersion, &jscriptMinorVersion)))
        {
            return 0;
        }

        if(!streamWriter.Write(jscriptMajorVersion))
        {
            return 0;
        }

        if(!streamWriter.Write(jscriptMinorVersion))
        {
            return 0;
        }

        if(!streamWriter.Write(startupFunctions->Length()))
        {
            return 0;
        }
        if(streamWriter.WriteArray(startupFunctions->GetData(), startupFunctions->WordCount()))
        {
            STATSTG stats;
            if(SUCCEEDED(writeStream->Stat(&stats, STATFLAG_NONAME)))
            {
                bytesWritten = stats.cbSize.LowPart;
                Assert(stats.cbSize.LowPart > 0);
                AssertMsg(stats.cbSize.HighPart == 0, "We should not be writing such long data that the high part is non-zero");
            }

            hr = profileDataCache->SaveWriteDataStream(writeStream);
            if(FAILED(hr))
            {
                return 0;
            }
#if DBG_DUMP
            if(PHASE_TRACE1(Js::DynamicProfilePhase) && Js::Configuration::Global.flags.Verbose)
            {
                OUTPUT_VERBOSE_TRACE(Js::DynamicProfilePhase, L"Saved profile:\n");
                startupFunctions->Dump();
            }
#endif
        }
#endif
        return bytesWritten;
    }