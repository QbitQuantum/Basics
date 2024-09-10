NTSTATUS
NTAPI
VdmpGetVdmTib(OUT PVDM_TIB *VdmTib)
{
    PVDM_TIB Tib;
    PAGED_CODE();

    /* Assume vailure */
    *VdmTib = NULL;

    /* Get the current TIB */
    Tib = NtCurrentTeb()->Vdm;
    if (!Tib) return STATUS_INVALID_SYSTEM_SERVICE;

    /* Validate the size */
    if (Tib->Size != sizeof(VDM_TIB)) return STATUS_INVALID_SYSTEM_SERVICE;

    /* Return it */
    *VdmTib = Tib;
    return STATUS_SUCCESS;
}