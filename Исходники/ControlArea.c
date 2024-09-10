NTSTATUS ControlAreaInitializeProcessor(LONG ProcessorNumber)
{
	//
	// Allocate host stack region
	// 16 pages available for use
	//
	SIZE_T stackSize = 16 * PAGE_SIZE;
	PUCHAR stackBase = ExAllocatePoolWithTag(NonPagedPool, stackSize, 'KSTK');

	if (!stackBase)
		return STATUS_NO_MEMORY;

	RtlSecureZeroMemory((PVOID)stackBase, stackSize);

	//
	// Set up CPU control structure
	//
	PVIRT_CPU cpu		= (PVIRT_CPU)(stackBase + stackSize - 8 - sizeof(VIRT_CPU));
	cpu->HostStackBase	= stackBase;
	cpu->Self			= cpu;

	CpuControlArea[ProcessorNumber] = cpu;

	//
	// Allocate all VMX regions
	//
	if (!NT_SUCCESS(AllocateVmxProcessorData(&cpu->VmxonVa, &cpu->VmxonPa, &cpu->VmxonSize)))
		return STATUS_NO_MEMORY;

	if (!NT_SUCCESS(AllocateVmxProcessorData(&cpu->VmcsVa, &cpu->VmcsPa, &cpu->VmcsSize)))
		return STATUS_NO_MEMORY;

	if (!NT_SUCCESS(AllocateVmxProcessorData(&cpu->MSRBitmapVa, &cpu->MSRBitmapPa, &cpu->MSRBitmapSize)))
		return STATUS_NO_MEMORY;

	// Bitmap needs to be zeroed
	RtlSecureZeroMemory(cpu->MSRBitmapVa, cpu->MSRBitmapSize);

	__try
	{
		if (__vmx_on(PA_PTR_INT64(cpu->VmxonPa)) > 0)
			return STATUS_UNSUCCESSFUL;

		if (__vmx_vmclear(PA_PTR_INT64(cpu->VmcsPa)) > 0)
			return STATUS_UNSUCCESSFUL;

		if (__vmx_vmptrld(PA_PTR_INT64(cpu->VmcsPa)) > 0)
			return STATUS_UNSUCCESSFUL;
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		// Rare case (or if physical address is invalid)
		return GetExceptionCode();
	}

	return STATUS_SUCCESS;
}