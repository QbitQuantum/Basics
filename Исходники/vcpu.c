static inline bool enter_vmx(struct vmcs *vmxon)
{
	/* If we're running nested on a hypervisor that does not
	 * support VT-x, this will cause #GP.  */
	u64 cr0 = __readcr0();
	cr0 &= __readmsr(MSR_IA32_VMX_CR0_FIXED1);
	cr0 |= __readmsr(MSR_IA32_VMX_CR0_FIXED0);
	__writecr0(cr0);

	u64 cr4 = __readcr4();
	cr4 &= __readmsr(MSR_IA32_VMX_CR4_FIXED1);
	cr4 |= __readmsr(MSR_IA32_VMX_CR4_FIXED0);
	__writecr4(cr4);

	u64 vmx = __readmsr(MSR_IA32_VMX_BASIC);
	vmxon->revision_id = (u32)vmx;

	/* Enter VMX root operation  */
	uintptr_t pa = __pa(vmxon);
	if (__vmx_on(&pa))
		return false;

	/* This is necessary here or just before we exit the VM,
	 * we do it here as it's easier.  */
	__invept_all();
	return true;
}