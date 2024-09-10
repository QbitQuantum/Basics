_Use_decl_annotations_ bool EptIsEptAvailable() {
  PAGED_CODE();

  int regs[4] = {};
  __cpuidex(regs, 0x80000008, 0);
  Cpuid80000008Eax cpuidEax = {static_cast<ULONG32>(regs[0])};
  HYPERPLATFORM_LOG_DEBUG("Physical Address Range = %d bits",
                          cpuidEax.fields.physical_address_bits);

  // No processors supporting the Intel 64 architecture support more than 48
  // physical-address bits
  if (cpuidEax.fields.physical_address_bits > 48) {
    return false;
  }

  // page walk length is 4 steps
  // extended page tables can be laid out in write-back memory
  // INVEPT instruction with all possible types is supported
  Ia32VmxEptVpidCapMsr vpid = {UtilReadMsr64(Msr::kIa32VmxEptVpidCap)};
  if (!vpid.fields.support_page_walk_length4 ||
      !vpid.fields.support_write_back_memory_type ||
      !vpid.fields.support_invept ||
      !vpid.fields.support_single_context_invept ||
      !vpid.fields.support_all_context_invept) {
    return false;
  }
  return true;
}