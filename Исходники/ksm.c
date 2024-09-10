static NTSTATUS set_lock_bit(void)
{
	uintptr_t feat_ctl = __readmsr(MSR_IA32_FEATURE_CONTROL);
	if (feat_ctl & FEATURE_CONTROL_LOCKED)
		return STATUS_SUCCESS;

	__writemsr(MSR_IA32_FEATURE_CONTROL, feat_ctl | FEATURE_CONTROL_LOCKED);
	feat_ctl = __readmsr(MSR_IA32_FEATURE_CONTROL);
	if (feat_ctl & FEATURE_CONTROL_LOCKED)
		return STATUS_SUCCESS;

	return STATUS_HV_ACCESS_DENIED;
}