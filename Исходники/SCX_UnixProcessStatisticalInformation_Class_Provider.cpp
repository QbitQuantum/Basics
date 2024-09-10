MI_BEGIN_NAMESPACE

static void EnumerateOneInstance(Context& context,
        SCX_UnixProcessStatisticalInformation_Class& inst, bool keysOnly,
        SCXCoreLib::SCXHandle<SCXSystemLib::ProcessInstance> processinst)
{
    SCXLogHandle& log = SCXCore::g_ProcessProvider.GetLogHandle();

    // Add the key properties first.
    scxulong pid;
    if (processinst->GetPID(pid))
    {
        inst.Handle_value(StrToUTF8(StrFrom(pid)).c_str());
    }

    // Add keys of scoping operating system
    try {
        SCXCoreLib::NameResolver mi;
        inst.CSName_value(StrToMultibyte(mi.GetHostDomainname()).c_str());
    } catch (SCXException& e){
        SCX_LOGWARNING(log, StrAppend(
                    StrAppend(L"Can't read host/domainname because ", e.What()),
                    e.Where()));
    }

    try {
        SCXSystemLib::SCXOSTypeInfo osinfo;
        inst.OSName_value(StrToMultibyte(osinfo.GetOSName(true)).c_str());
    } catch (SCXException& e){
        SCX_LOGWARNING(log, StrAppend(
                    StrAppend(L"Can't read OS name because ", e.What()),
                    e.Where()));
    }

    inst.CSCreationClassName_value("SCX_ComputerSystem");
    inst.OSCreationClassName_value("SCX_OperatingSystem");
    inst.ProcessCreationClassName_value("SCX_UnixProcessStatisticalInformation");

    std::string name;
    if (processinst->GetName(name))
    {
        inst.Name_value(name.c_str());
    }

    if (!keysOnly)
    {
        unsigned int uint = 0;
        scxulong ulong = 0;

        inst.Description_value("A snapshot of a current process");
        inst.Caption_value("Unix process information");

        if (processinst->GetRealData(ulong))
        {
            inst.RealData_value(ulong);
        }

        if (processinst->GetRealStack(ulong))
        {
            inst.RealStack_value(ulong);
        }

        if (processinst->GetVirtualText(ulong))
        {
            inst.VirtualText_value(ulong);
        }

        if (processinst->GetVirtualData(ulong))
        {
            inst.VirtualData_value(ulong);
        }

        if (processinst->GetVirtualStack(ulong))
        {
            inst.VirtualStack_value(ulong);
        }

        if (processinst->GetVirtualMemoryMappedFileSize(ulong))
        {
            inst.VirtualMemoryMappedFileSize_value(ulong);
        }

        if (processinst->GetVirtualSharedMemory(ulong))
        {
            inst.VirtualSharedMemory_value(ulong);
        }

        if (processinst->GetCpuTimeDeadChildren(ulong))
        {
            inst.CpuTimeDeadChildren_value(ulong);
        }

        if (processinst->GetSystemTimeDeadChildren(ulong))
        {
            inst.SystemTimeDeadChildren_value(ulong);
        }

        if (processinst->GetRealText(ulong))
        {
            inst.RealText_value(ulong);
        }

        if (processinst->GetCPUTime(uint))
        {
            inst.CPUTime_value(uint);
        }

        if (processinst->GetBlockWritesPerSecond(ulong))
        {
            inst.BlockWritesPerSecond_value(ulong);
        }

        if (processinst->GetBlockReadsPerSecond(ulong))
        {
            inst.BlockReadsPerSecond_value(ulong);
        }

        if (processinst->GetBlockTransfersPerSecond(ulong))
        {
            inst.BlockTransfersPerSecond_value(ulong);
        }

        if (processinst->GetPercentUserTime(ulong))
        {
            inst.PercentUserTime_value((unsigned char) ulong);
        }

        if (processinst->GetPercentPrivilegedTime(ulong))
        {
            inst.PercentPrivilegedTime_value((unsigned char) ulong);
        }

        if (processinst->GetUsedMemory(ulong))
        {
            inst.UsedMemory_value(ulong);
        }

        if (processinst->GetPercentUsedMemory(ulong))
        {
            inst.PercentUsedMemory_value((unsigned char) ulong);
        }

        if (processinst->GetPagesReadPerSec(ulong))
        {
            inst.PagesReadPerSec_value(ulong);
        }
    }
    context.Post(inst);
}