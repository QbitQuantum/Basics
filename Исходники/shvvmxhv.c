DECLSPEC_NORETURN
EXTERN_C
VOID
ShvVmxEntryHandler (
    _In_ PCONTEXT Context
    )
{
    SHV_VP_STATE guestContext;
    PSHV_VP_DATA vpData;

    //
    // Because we run with interrupts disabled during the entire hypervisor's
    // exit handling, raise the IRQL to HIGH_LEVEL which matches the reality of
    // the situation. This will block IPIs and the clock interrupt timer, which
    // means that it's critical to spend as little time here as possible. You
    // can expect CLOCK_WATCHDOG_TIMEOUT bugchecks to happen otherwise. If you
    // chose to enable interrupts note that this will result in further crashes
    // as we are not on a correct OS stack, and you will be hitting crashes if
    // RtlpCheckStackLimits is ever called, or if PatchGuard validates the RSP
    // value.
    //
    KeRaiseIrql(HIGH_LEVEL, &guestContext.GuestIrql);

    //
    // Because we had to use RCX when calling RtlCaptureContext, its true value
    // was actually pushed on the stack right before the call. Go dig into the
    // stack to find it, and overwrite the bogus value that's there now.
    //
    Context->Rcx = *(PULONG64)((ULONG_PTR)Context - sizeof(Context->Rcx));

    //
    // Get the per-VP data for this processor.
    //
    vpData = &ShvGlobalData->VpData[KeGetCurrentProcessorNumberEx(NULL)];

    //
    // Build a little stack context to make it easier to keep track of certain
    // guest state, such as the RIP/RSP/RFLAGS, and the exit reason. The rest
    // of the general purpose registers come from the context structure that we
    // captured on our own with RtlCaptureContext in the assembly entrypoint.
    //
    guestContext.GuestEFlags = ShvVmxRead(GUEST_RFLAGS);
    guestContext.GuestRip = ShvVmxRead(GUEST_RIP);
    guestContext.GuestRsp = ShvVmxRead(GUEST_RSP);
    guestContext.ExitReason = ShvVmxRead(VM_EXIT_REASON) & 0xFFFF;
    guestContext.VpRegs = Context;
    guestContext.ExitVm = FALSE;

    //
    // Call the generic handler
    //
    ShvVmxHandleExit(&guestContext);

    //
    // Did we hit the magic exit sequence, or should we resume back to the VM
    // context?
    //
    if (guestContext.ExitVm)
    {
        //
        // When running in VMX root mode, the processor will set limits of the
        // GDT and IDT to 0xFFFF (notice that there are no Host VMCS fields to
        // set these values). This causes problems with PatchGuard, which will
        // believe that the GDTR and IDTR have been modified by malware, and
        // eventually crash the system. Since we know what the original state
        // of the GDTR and IDTR was, simply restore it now.
        //
        __lgdt(&vpData->HostState.SpecialRegisters.Gdtr.Limit);
        __lidt(&vpData->HostState.SpecialRegisters.Idtr.Limit);

        //
        // Our DPC routine may have interrupted an arbitrary user process, and
        // not an idle or system thread as usually happens on an idle system.
        // Therefore if we return back to the original caller after turning off
        // VMX, it will keep our current "host" CR3 value which we set on entry
        // to the PML4 of the SYSTEM process. We want to return back with the
        // correct value of the "guest" CR3, so that the currently executing
        // process continues to run with its expected address space mappings.
        //
        __writecr3(ShvVmxRead(GUEST_CR3));

        //
        // Finally, set the stack and instruction pointer to whatever location
        // had the instruction causing our VM-Exit, such as ShvVpUninitialize.
        // This will effectively act as a longjmp back to that location.
        //
        Context->Rsp = guestContext.GuestRsp;
        Context->Rip = (ULONG64)guestContext.GuestRip;

        //
        // Turn off VMX root mode on this logical processor. We're done here.
        //
        __vmx_off();
    }
    else
    {
        //
        // Because we won't be returning back into assembly code, nothing will
        // ever know about the "pop rcx" that must technically be done (or more
        // accurately "add rsp, 4" as rcx will already be correct thanks to the
        // fixup earlier. In order to keep the stack sane, do that adjustment
        // here.
        //
        Context->Rsp += sizeof(Context->Rcx);

        //
        // Return into a VMXRESUME intrinsic, which we broke out as its own
        // function, in order to allow this to work. No assembly code will be
        // needed as RtlRestoreContext will fix all the GPRs, and what we just
        // did to RSP will take care of the rest.
        //
        Context->Rip = (ULONG64)ShvVmxResume;
    }

    //
    // Restore the IRQL back to the original level
    //
    KeLowerIrql(guestContext.GuestIrql);

    //
    // Restore the context to either ShvVmxResume, in which case the CPU's VMX
    // facility will do the "true" return back to the VM (but without restoring
    // GPRs, which is why we must do it here), or to the original guest's RIP,
    // which we use in case an exit was requested. In this case VMX must now be
    // off, and this will look like a longjmp to the original stack and RIP.
    //
    RtlRestoreContext(Context, NULL);
}