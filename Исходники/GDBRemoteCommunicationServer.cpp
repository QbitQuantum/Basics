static void
CreateProcessInfoResponse (const ProcessInstanceInfo &proc_info, StreamString &response)
{
    response.Printf ("pid:%llu;ppid:%llu;uid:%i;gid:%i;euid:%i;egid:%i;", 
                     proc_info.GetProcessID(),
                     proc_info.GetParentProcessID(),
                     proc_info.GetUserID(),
                     proc_info.GetGroupID(),
                     proc_info.GetEffectiveUserID(),
                     proc_info.GetEffectiveGroupID());
    response.PutCString ("name:");
    response.PutCStringAsRawHex8(proc_info.GetName());
    response.PutChar(';');
    const ArchSpec &proc_arch = proc_info.GetArchitecture();
    if (proc_arch.IsValid())
    {
        const llvm::Triple &proc_triple = proc_arch.GetTriple();
        response.PutCString("triple:");
        response.PutCStringAsRawHex8(proc_triple.getTriple().c_str());
        response.PutChar(';');
    }
}