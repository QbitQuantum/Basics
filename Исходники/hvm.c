static FORCEINLINE NTSTATUS
__InitHypercallPage()
{
    ULONG   eax = 'DEAD';
    ULONG   ebx = 'DEAD';
    ULONG   ecx = 'DEAD';
    ULONG   edx = 'DEAD';
    ULONG   Index;
    ULONG   HypercallMsr;

    NTSTATUS    Status;

    Status = STATUS_UNSUCCESSFUL;
    for (;;) {
        CHAR Signature[13] = { 0 };

        CpuId(__BaseLeaf, &eax, &ebx, &ecx, &edx);
        *((PULONG)(Signature + 0)) = ebx;
        *((PULONG)(Signature + 4)) = ecx;
        *((PULONG)(Signature + 8)) = edx;

        if (strcmp(Signature, XEN_SIGNATURE) == 0 &&
            eax >= __BaseLeaf + 2)
            break;

        __BaseLeaf += 0x100;

        if (__BaseLeaf > 0x40000100)
            goto fail1;
    }

    CpuId(__BaseLeaf + 1, &eax, NULL, NULL, NULL);
    __MajorVersion = (USHORT)(eax >> 16);
    __MinorVersion = (USHORT)(eax & 0xFFFF);

    LogVerbose("XEN %d.%d\n", __MajorVersion, __MinorVersion);
    LogVerbose("INTERFACE 0x%08x\n", __XEN_INTERFACE_VERSION__);

    if ((ULONG_PTR)__HypercallSection & (PAGE_SIZE - 1))
        Hypercall = (PVOID)(((ULONG_PTR)__HypercallSection + PAGE_SIZE - 1) & ~(PAGE_SIZE - 1));
    else
        Hypercall = (PVOID)__HypercallSection;

    ASSERT3U(((ULONG_PTR)Hypercall & (PAGE_SIZE - 1)), ==, 0);

    for (Index = 0; Index < MAXIMUM_HYPERCALL_PFN_COUNT; Index++) {
        PHYSICAL_ADDRESS    PhysicalAddress;

        PhysicalAddress = MmGetPhysicalAddress((PUCHAR)Hypercall + (Index << PAGE_SHIFT));
        __Pfn[Index] = (PFN_NUMBER)(PhysicalAddress.QuadPart >> PAGE_SHIFT);
    }

    CpuId(__BaseLeaf + 2, &eax, &ebx, NULL, NULL);
    __PfnCount = eax;
    ASSERT(__PfnCount <= MAXIMUM_HYPERCALL_PFN_COUNT);
    HypercallMsr = ebx;

    for (Index = 0; Index < __PfnCount; Index++) {
        LogVerbose("HypercallPfn[%d]: %p\n", Index, (PVOID)__Pfn[Index]);
        __writemsr(HypercallMsr, (ULONG64)__Pfn[Index] << PAGE_SHIFT);
    }

    return STATUS_SUCCESS;

fail1:
    LogError("fail1 (%08x)", Status);

    return Status;
}