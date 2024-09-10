    /**
       Add a SCXInstance with the name property set frmo the ProcessInstance to the collection

       \param[in]   processinst    Process instance to get data from
       \param[out]  inst           Instance to add keys to
       \param[in]   cimtype        Type of CIM Class to return

       \throws      SCXInvalidArgumentException - The instance can not be converted to a ProcessInstance

       This method contains knowledge on which are the key fields for the class.
       The key properties are defined in the MOF file.

    */
    void ProcessProvider::AddKeys(SCXCoreLib::SCXHandle<SCXSystemLib::ProcessInstance> processinst, SCXInstance &inst, SupportedCimClasses cimtype) // private
    {
        SCX_LOGTRACE(m_log, L"ProcessProvider AddKeys()");

        if (processinst == NULL)
        {
            throw SCXInvalidArgumentException(L"einst", L"Not a ProcessInstance", SCXSRCLOCATION);
        }

        scxulong pid;
        if (processinst->GetPID(pid))
        {
            SCXProperty pid_prop(L"Handle", StrFrom(pid));
            inst.AddKey(pid_prop);
        }

        AddScopingOperatingSystemKeys(inst);
        if (eSCX_UnixProcessStatisticalInformation == cimtype)
        {
            std::string name;
            if (processinst->GetName(name))
            {
                SCXProperty name_prop(L"Name", StrFromMultibyte(name));
                inst.AddKey(name_prop);
                SCXProperty creationClass_prop(L"ProcessCreationClassName", L"SCX_UnixProcessStatisticalInformation");
                inst.AddKey(creationClass_prop);
            }
        }
        else if (eSCX_UnixProcess == cimtype)
        {
            SCXProperty creationClass_prop(L"CreationClassName", L"SCX_UnixProcess");
            inst.AddKey(creationClass_prop);
        }

    }