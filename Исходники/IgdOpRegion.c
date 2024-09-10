/**
  Get Intel GOP driver version and copy it into IGD OpRegion GVER. This version
  is picked up by IGD driver and displayed in CUI.

  @param  Event             A pointer to the Event that triggered the callback.
  @param  Context           A pointer to private data registered with the callback function.

  @retval EFI_SUCCESS       Video BIOS VBT information returned.
  @retval EFI_UNSUPPORTED   Could not find VBT information (*VBiosVbtPtr = NULL).

**/
EFI_STATUS
EFIAPI
SetGOPVersionCallback (
    IN EFI_EVENT Event,
    IN VOID      *Context
)
{
    CHAR16                GopVersion[16] = {0};
    EFI_STATUS            Status;

    Status = GetGOPDriverVersion(GopVersion);
    if(!EFI_ERROR(Status)) {
        StrCpy((CHAR16*)&(mIgdOpRegion.OpRegion->Header.GOPV[0]), GopVersion);
        return Status;
    }
    return EFI_UNSUPPORTED;
}