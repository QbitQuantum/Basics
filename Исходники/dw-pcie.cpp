/*
 * Program a region into the outbound ATU
 * The ATU supports 16 regions that can be programmed independently.
 *   pcie,              PCIe Device Struct
 *   index,             Which iATU region are we programming?
 *   type,              Type of PCIe txn being generated on the PCIe bus
 *   cpu_addr,          Physical source address to translate in the CPU's address space
 *   pci_addr,          Destination Address in the PCIe address space
 *   size               Size of the aperature that we're translating.
 */
zx_status_t DwPcie::ProgramOutboundAtu(const uint32_t index,
                                       const uint32_t type,
                                       const zx_paddr_t cpu_addr,
                                       const uintptr_t pci_addr,
                                       const size_t size) {
    // The ATU supports a limited number of regions.
    ZX_DEBUG_ASSERT(index < kAtuRegionCount);

    // Each ATU region has its own bank of registers at this offset from the
    // DBI base
    const size_t bank_offset = (0x3 << 20) | (index << 9);
    volatile uint8_t* atu_base =
        reinterpret_cast<volatile uint8_t*>(dbi_.get()) + bank_offset;

    volatile atu_ctrl_regs_t* regs =
        reinterpret_cast<volatile atu_ctrl_regs_t*>(atu_base);

    // Memory transactions that are in the following range will get translated
    // to PCI bus transactions:
    //
    // [cpu_addr, cpu_addr + size - 1]
    regs->unroll_lower_base = lo32(cpu_addr);
    regs->unroll_upper_base = hi32(cpu_addr);

    regs->unroll_limit = lo32(cpu_addr + size - 1);

    // Target of the transactions above.
    regs->unroll_lower_target = lo32(pci_addr);
    regs->unroll_upper_target = hi32(pci_addr);

    // Region Ctrl 1 contains a number of fields. The Low 5 bits of the field
    // indicate the type of transaction to dispatch onto the PCIe bus.
    regs->region_ctrl1 = type;

    // Each region can individually be marked as Enabled or Disabled.
    regs->region_ctrl2 |= kAtuRegionCtrlEnable;
    regs->region_ctrl2 |= kAtuCfgShiftMode;

    // Wait for the enable to take effect.
    for (unsigned int i = 0; i < kAtuProgramRetries; ++i) {
        if (regs->region_ctrl2 & kAtuRegionCtrlEnable) {
            return ZX_OK;
        }

        // Wait a little bit before trying again.
        zx_nanosleep(zx_deadline_after(ZX_USEC(kAtuWaitEnableTimeoutUs)));
    }

    return ZX_ERR_TIMED_OUT;
}