// Handles #BP. Determinas if the #BP is caused by a shadow breakpoint, and if
// so, runs its handler, switchs a page view to read/write shadow page and sets
// the monitor trap flag to execute only one instruction where is located on the
// read/write shadow page. Then saves the breakpoint info as the last event.
_Use_decl_annotations_ bool SbpHandleBreakpoint(EptData* ept_data,
                                                void* guest_ip,
                                                GpRegisters* gp_regs) {
  if (!SbppIsSbpActive()) {
    return false;
  }

  const auto info = SbppFindPatchInfoByAddress(guest_ip);
  if (!info) {
    return false;
  }

  if (!SbppIsShadowBreakpoint(*info)) {
    return false;
  }

  // DdiMon is unable to handle it
  if (KeGetCurrentIrql() > DISPATCH_LEVEL) {
    HYPERPLATFORM_COMMON_BUG_CHECK(HyperPlatformBugCheck::kUnspecified, 0, 0,
                                   0);
  }

  // VMM has to change the current CR3 to a guest's CR3 in order to access
  // memory address because VMM runs with System's CR3 saved in and restored
  // from
  // VmcsField::kHostCr3, while a guest's CR3 is depends on thread contexts.
  // Without using guest's CR3, it is likely that any use-address space is
  // inaccessible from a VMM ending up with a bug check.
  const auto guest_cr3 = UtilVmRead(VmcsField::kGuestCr3);
  const auto vmm_cr3 = __readcr3();

  if (info->type == BreakpointType::kPre) {
    // Pre breakpoint
    __writecr3(guest_cr3);
    info->handler(*info, ept_data, gp_regs, UtilVmRead(VmcsField::kGuestRsp));
    __writecr3(vmm_cr3);
    SbppEnablePageShadowingForRW(*info, ept_data);
    SbppSetMonitorTrapFlag(true);
    SbppSaveLastPatchInfo(*info);

  } else {
    // Post breakpoint
    if (info->target_tid == PsGetCurrentThreadId()) {
      // It is a target thread. Execute the post handler and let it continue
      // subsequence instructions.
      __writecr3(guest_cr3);
      info->handler(*info, ept_data, gp_regs, UtilVmRead(VmcsField::kGuestRsp));
      __writecr3(vmm_cr3);
      SbppDisablePageShadowing(*info, ept_data);
      SbppDeleteBreakpointFromList(*info);
    } else {
      // It is not. Let it allow to run one instruction without breakpoint
      SbppEnablePageShadowingForRW(*info, ept_data);
      SbppSetMonitorTrapFlag(true);
      SbppSaveLastPatchInfo(*info);
    }
  }

  // Yes, it was caused by shadow breakpoint. Do not deliver the #BP to a guest.
  return true;
}