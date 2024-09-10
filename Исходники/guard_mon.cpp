// Modifies IDTL so that PatchGuard fires soon.
_Use_decl_annotations_ NTSTATUS GMonInstallPatchCallback(void *context) {
  UNREFERENCED_PARAMETER(context);

  Idtr idt = {};
  __sidt(&idt);
  const auto old_limit = idt.limit;
  idt.limit = 0xffff;
  __lidt(&idt);
  __sidt(&idt);
  HYPERPLATFORM_LOG_INFO("Patched IDTL %04hx => %04hx", old_limit, idt.limit);
  return STATUS_SUCCESS;
}