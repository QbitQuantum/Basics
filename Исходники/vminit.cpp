_Use_decl_annotations_ EXTERN_C static bool VminitpEnterVmxMode(
    PER_PROCESSOR_DATA *ProcessorData) {
  // Apply FIXED bits
  const CR0_REG cr0Fixed0 = {__readmsr(IA32_VMX_CR0_FIXED0)};
  const CR0_REG cr0Fixed1 = {__readmsr(IA32_VMX_CR0_FIXED1)};
  CR0_REG cr0 = {__readcr0()};
  cr0.All &= cr0Fixed1.All;
  cr0.All |= cr0Fixed0.All;
  __writecr0(cr0.All);

  const CR4_REG cr4Fixed0 = {__readmsr(IA32_VMX_CR4_FIXED0)};
  const CR4_REG cr4Fixed1 = {__readmsr(IA32_VMX_CR4_FIXED1)};
  CR4_REG cr4 = {__readcr4()};
  cr4.All &= cr4Fixed1.All;
  cr4.All |= cr4Fixed0.All;
  __writecr4(cr4.All);

  // Write a VMCS revision identifier
  IA32_VMX_BASIC_MSR vmxBasicMsr = {__readmsr(IA32_VMX_BASIC)};
  ProcessorData->VmxonRegion->RevisionIdentifier =
      vmxBasicMsr.Fields.RevisionIdentifier;

  auto vmxonRegionPA = MmGetPhysicalAddress(ProcessorData->VmxonRegion);
  if (__vmx_on(
          reinterpret_cast<unsigned long long *>(&vmxonRegionPA.QuadPart))) {
    return false;
  }
  return true;
}