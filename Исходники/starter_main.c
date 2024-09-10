void save_cpu_state(mon_guest_cpu_startup_state_t *s)
{
	ia32_gdtr_t gdtr;
	ia32_idtr_t idtr;
	ia32_selector_t sel;
	ia32_segment_descriptor_t *desc;

	s->size_of_this_struct = sizeof(mon_guest_cpu_startup_state_t);
	s->version_of_this_struct = MON_GUEST_CPU_STARTUP_STATE_VERSION;

	__readgdtr(&gdtr);
	__sidt(&idtr);
	s->control.gdtr.base = (uint64_t)gdtr.base;
	s->control.gdtr.limit = (uint32_t)gdtr.limit;
	s->control.idtr.base = (uint64_t)idtr.base;
	s->control.idtr.limit = (uint32_t)idtr.limit;
	s->control.cr[IA32_CTRL_CR0] = __readcr0();
	s->control.cr[IA32_CTRL_CR2] = __readcr2();
	s->control.cr[IA32_CTRL_CR3] = __readcr3();
	s->control.cr[IA32_CTRL_CR4] = __readcr4();

	s->msr.msr_sysenter_cs = (uint32_t)__readmsr(IA32_MSR_SYSENTER_CS);
	s->msr.msr_sysenter_eip = __readmsr(IA32_MSR_SYSENTER_EIP);
	s->msr.msr_sysenter_esp = __readmsr(IA32_MSR_SYSENTER_ESP);
	s->msr.msr_efer = __readmsr(IA32_MSR_EFER);
	s->msr.msr_pat = __readmsr(IA32_MSR_PAT);
	s->msr.msr_debugctl = __readmsr(IA32_MSR_DEBUGCTL);
	s->msr.pending_exceptions = 0;
	s->msr.interruptibility_state = 0;
	s->msr.activity_state = 0;
	s->msr.smbase = 0;

	sel.sel16 = __readldtr();

	if (sel.bits.index != 0) {
		return;
	}

	s->seg.segment[IA32_SEG_LDTR].attributes = 0x00010000;
	s->seg.segment[IA32_SEG_TR].attributes = 0x0000808b;
	s->seg.segment[IA32_SEG_TR].limit = 0xffffffff;
	save_segment_data((uint16_t)__readcs(), &s->seg.segment[IA32_SEG_CS]);
	save_segment_data((uint16_t)__readds(), &s->seg.segment[IA32_SEG_DS]);
	save_segment_data((uint16_t)__reades(), &s->seg.segment[IA32_SEG_ES]);
	save_segment_data((uint16_t)__readfs(), &s->seg.segment[IA32_SEG_FS]);
	save_segment_data((uint16_t)__readgs(), &s->seg.segment[IA32_SEG_GS]);
	save_segment_data((uint16_t)__readss(), &s->seg.segment[IA32_SEG_SS]);
	return;
}