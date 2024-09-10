// Try and figure out where dyld is by first asking the Process if it knows
// (which currently calls down in the lldb::Process to get the DYLD info
// (available on SnowLeopard only). If that fails, then check in the default
// addresses.
void DynamicLoaderMacOSXDYLD::DoInitialImageFetch() {
  if (m_dyld_all_image_infos_addr == LLDB_INVALID_ADDRESS) {
    // Check the image info addr as it might point to the mach header for dyld,
    // or it might point to the dyld_all_image_infos struct
    const addr_t shlib_addr = m_process->GetImageInfoAddress();
    if (shlib_addr != LLDB_INVALID_ADDRESS) {
      ByteOrder byte_order =
          m_process->GetTarget().GetArchitecture().GetByteOrder();
      uint8_t buf[4];
      DataExtractor data(buf, sizeof(buf), byte_order, 4);
      Status error;
      if (m_process->ReadMemory(shlib_addr, buf, 4, error) == 4) {
        lldb::offset_t offset = 0;
        uint32_t magic = data.GetU32(&offset);
        switch (magic) {
        case llvm::MachO::MH_MAGIC:
        case llvm::MachO::MH_MAGIC_64:
        case llvm::MachO::MH_CIGAM:
        case llvm::MachO::MH_CIGAM_64:
          m_process_image_addr_is_all_images_infos = false;
          ReadDYLDInfoFromMemoryAndSetNotificationCallback(shlib_addr);
          return;

        default:
          break;
        }
      }
      // Maybe it points to the all image infos?
      m_dyld_all_image_infos_addr = shlib_addr;
      m_process_image_addr_is_all_images_infos = true;
    }
  }

  if (m_dyld_all_image_infos_addr != LLDB_INVALID_ADDRESS) {
    if (ReadAllImageInfosStructure()) {
      if (m_dyld_all_image_infos.dyldImageLoadAddress != LLDB_INVALID_ADDRESS)
        ReadDYLDInfoFromMemoryAndSetNotificationCallback(
            m_dyld_all_image_infos.dyldImageLoadAddress);
      else
        ReadDYLDInfoFromMemoryAndSetNotificationCallback(
            m_dyld_all_image_infos_addr & 0xfffffffffff00000ull);
      return;
    }
  }

  // Check some default values
  Module *executable = m_process->GetTarget().GetExecutableModulePointer();

  if (executable) {
    const ArchSpec &exe_arch = executable->GetArchitecture();
    if (exe_arch.GetAddressByteSize() == 8) {
      ReadDYLDInfoFromMemoryAndSetNotificationCallback(0x7fff5fc00000ull);
    } else if (exe_arch.GetMachine() == llvm::Triple::arm ||
               exe_arch.GetMachine() == llvm::Triple::thumb ||
               exe_arch.GetMachine() == llvm::Triple::aarch64) {
      ReadDYLDInfoFromMemoryAndSetNotificationCallback(0x2fe00000);
    } else {
      ReadDYLDInfoFromMemoryAndSetNotificationCallback(0x8fe00000);
    }
  }
  return;
}