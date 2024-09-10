static void
init_interrupt_handler(intel_info &info)
{
	info.shared_info->vblank_sem = create_sem(0, "intel extreme vblank");
	if (info.shared_info->vblank_sem < B_OK)
		return;

	status_t status = B_OK;

	// We need to change the owner of the sem to the calling team (usually the
	// app_server), because userland apps cannot acquire kernel semaphores
	thread_id thread = find_thread(NULL);
	thread_info threadInfo;
	if (get_thread_info(thread, &threadInfo) != B_OK
		|| set_sem_owner(info.shared_info->vblank_sem, threadInfo.team)
			!= B_OK) {
		status = B_ERROR;
	}

	// Find the right interrupt vector, using MSIs if available.
	info.irq = 0xff;
	info.use_msi = false;	
	if (info.pci->u.h0.interrupt_pin != 0x00)	
		info.irq = info.pci->u.h0.interrupt_line;
	if (gPCIx86Module != NULL && gPCIx86Module->get_msi_count(info.pci->bus,
			info.pci->device, info.pci->function) >= 1) {
		uint8 msiVector = 0;
		if (gPCIx86Module->configure_msi(info.pci->bus, info.pci->device,
				info.pci->function, 1, &msiVector) == B_OK
			&& gPCIx86Module->enable_msi(info.pci->bus, info.pci->device,
				info.pci->function) == B_OK) {
			ERROR("using message signaled interrupts\n");
			info.irq = msiVector;
			info.use_msi = true;
		}
	}

	if (status == B_OK && info.irq != 0xff) {
		// we've gotten an interrupt line for us to use

		info.fake_interrupts = false;

		status = install_io_interrupt_handler(info.irq,
			&intel_interrupt_handler, (void*)&info, 0);
		if (status == B_OK) {
			write32(info, INTEL_DISPLAY_A_PIPE_STATUS,
				DISPLAY_PIPE_VBLANK_STATUS | DISPLAY_PIPE_VBLANK_ENABLED);
			write32(info, INTEL_DISPLAY_B_PIPE_STATUS,
				DISPLAY_PIPE_VBLANK_STATUS | DISPLAY_PIPE_VBLANK_ENABLED);

			write16(info, find_reg(info, INTEL_INTERRUPT_IDENTITY), ~0);

			// enable interrupts - we only want VBLANK interrupts
			bool hasPCH = info.device_type.HasPlatformControlHub();
			uint16 enable = hasPCH
				? (PCH_INTERRUPT_VBLANK_PIPEA | PCH_INTERRUPT_VBLANK_PIPEB)
				: (INTERRUPT_VBLANK_PIPEA | INTERRUPT_VBLANK_PIPEB);

			write16(info, find_reg(info, INTEL_INTERRUPT_ENABLED), enable);
			write16(info, find_reg(info, INTEL_INTERRUPT_MASK), ~enable);
		}
	}
	if (status < B_OK) {
		// There is no interrupt reserved for us, or we couldn't install our
		// interrupt handler, let's fake the vblank interrupt for our clients
		// using a timer interrupt
		info.fake_interrupts = true;

		// TODO: fake interrupts!
		TRACE("Fake interrupt mode (no PCI interrupt line assigned\n");
		status = B_ERROR;
	}

	if (status < B_OK) {
		delete_sem(info.shared_info->vblank_sem);
		info.shared_info->vblank_sem = B_ERROR;
	}
}