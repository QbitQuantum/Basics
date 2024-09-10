void GDBRemoteCommunicationServerCommon::
    CreateProcessInfoResponse_DebugServerStyle(
        const ProcessInstanceInfo &proc_info, StreamString &response) {
  response.Printf("pid:%" PRIx64 ";parent-pid:%" PRIx64
                  ";real-uid:%x;real-gid:%x;effective-uid:%x;effective-gid:%x;",
                  proc_info.GetProcessID(), proc_info.GetParentProcessID(),
                  proc_info.GetUserID(), proc_info.GetGroupID(),
                  proc_info.GetEffectiveUserID(),
                  proc_info.GetEffectiveGroupID());

  const ArchSpec &proc_arch = proc_info.GetArchitecture();
  if (proc_arch.IsValid()) {
    const llvm::Triple &proc_triple = proc_arch.GetTriple();
#if defined(__APPLE__)
    // We'll send cputype/cpusubtype.
    const uint32_t cpu_type = proc_arch.GetMachOCPUType();
    if (cpu_type != 0)
      response.Printf("cputype:%" PRIx32 ";", cpu_type);

    const uint32_t cpu_subtype = proc_arch.GetMachOCPUSubType();
    if (cpu_subtype != 0)
      response.Printf("cpusubtype:%" PRIx32 ";", cpu_subtype);

    const std::string vendor = proc_triple.getVendorName();
    if (!vendor.empty())
      response.Printf("vendor:%s;", vendor.c_str());
#else
    // We'll send the triple.
    response.PutCString("triple:");
    response.PutCStringAsRawHex8(proc_triple.getTriple().c_str());
    response.PutChar(';');
#endif
    std::string ostype = proc_triple.getOSName();
    // Adjust so ostype reports ios for Apple/ARM and Apple/ARM64.
    if (proc_triple.getVendor() == llvm::Triple::Apple) {
      switch (proc_triple.getArch()) {
      case llvm::Triple::arm:
      case llvm::Triple::thumb:
      case llvm::Triple::aarch64:
        ostype = "ios";
        break;
      default:
        // No change.
        break;
      }
    }
    response.Printf("ostype:%s;", ostype.c_str());

    switch (proc_arch.GetByteOrder()) {
    case lldb::eByteOrderLittle:
      response.PutCString("endian:little;");
      break;
    case lldb::eByteOrderBig:
      response.PutCString("endian:big;");
      break;
    case lldb::eByteOrderPDP:
      response.PutCString("endian:pdp;");
      break;
    default:
      // Nothing.
      break;
    }
    // In case of MIPS64, pointer size is depend on ELF ABI
    // For N32 the pointer size is 4 and for N64 it is 8
    std::string abi = proc_arch.GetTargetABI();
    if (!abi.empty())
      response.Printf("elf_abi:%s;", abi.c_str());
    response.Printf("ptrsize:%d;", proc_arch.GetAddressByteSize());
  }
}