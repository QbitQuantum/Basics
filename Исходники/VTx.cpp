NTSTATUS VTxSoftwareStatus()
{
	//
	// Check the feature control bit MSR
	//
	IA32_FEATURE_CONTROL_MSR msr;
	TO_ULL(msr) = __readmsr(MSR_IA32_FEATURE_CONTROL);

	if (msr.Lock == 1)
	{
		// If the MSR is locked, it can't be modified
		// If 'EnableVmxon' is unset, virtualization is not possible
		if (msr.EnableVmxon == 0)
		{
			DbgLog("VMX is disabled in bios: MSR_IA32_FEATURE_CONTROL is 0x%llx\n", msr);
			return STATUS_NOT_SUPPORTED;
		}
	}
	else
	{
		// Force the lock to be on and enable VMXON
		msr.Lock		= 1;
		msr.VmxonInSmx	= 1;
		msr.EnableVmxon = 1;

		__writemsr(MSR_IA32_FEATURE_CONTROL, TO_ULL(msr));
	}

	//
	// Setup CR0 correctly (Protected mode and paging must be enabled)
	//
	CR0_REG cr0;
	TO_ULL(cr0) = __readcr0();

	if (cr0.PE == 0 || cr0.PG == 0)
	{
		DbgLog("Error: Protected mode or paging is not set in CR0\n");
		return STATUS_NOT_SUPPORTED;
	}
	else
	{
		// Required by first processors that supported VMX
		cr0.NE = 1;
	}

	__writecr0(TO_ULL(cr0));

	//
	// Virtual Machine eXtensions Enable in CR4
	// BIT #13 VMXE
	//
	__try
	{
		__writecr4(__readcr4() | (1 << 13));
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		// Possible 'Privileged Instruction Exception' with CR4 bits
		return GetExceptionCode();
	}

	return STATUS_SUCCESS;
}