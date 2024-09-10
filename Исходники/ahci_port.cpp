status_t
AHCIPort::Init1()
{
    TRACE("AHCIPort::Init1 port %d\n", fIndex);

    size_t size = sizeof(command_list_entry) * COMMAND_LIST_ENTRY_COUNT
                  + sizeof(fis) + sizeof(command_table)
                  + sizeof(prd) * PRD_TABLE_ENTRY_COUNT;

    char *virtAddr;
    phys_addr_t physAddr;

    fArea = alloc_mem((void **)&virtAddr, &physAddr, size, 0,
                      "some AHCI port");
    if (fArea < B_OK) {
        TRACE("failed allocating memory for port %d\n", fIndex);
        return fArea;
    }
    memset(virtAddr, 0, size);

    fCommandList = (command_list_entry *)virtAddr;
    virtAddr += sizeof(command_list_entry) * COMMAND_LIST_ENTRY_COUNT;
    fFIS = (fis *)virtAddr;
    virtAddr += sizeof(fis);
    fCommandTable = (command_table *)virtAddr;
    virtAddr += sizeof(command_table);
    fPRDTable = (prd *)virtAddr;
    TRACE("PRD table is at %p\n", fPRDTable);

    fRegs->clb  = LO32(physAddr);
    fRegs->clbu = HI32(physAddr);
    physAddr += sizeof(command_list_entry) * COMMAND_LIST_ENTRY_COUNT;
    fRegs->fb   = LO32(physAddr);
    fRegs->fbu  = HI32(physAddr);
    physAddr += sizeof(fis);
    fCommandList[0].ctba  = LO32(physAddr);
    fCommandList[0].ctbau = HI32(physAddr);
    // prdt follows after command table

    // disable transitions to partial or slumber state
    fRegs->sctl |= 0x300;

    // clear IRQ status bits
    fRegs->is = fRegs->is;

    // clear error bits
    fRegs->serr = fRegs->serr;

    // power up device
    fRegs->cmd |= PORT_CMD_POD;

    // spin up device
    fRegs->cmd |= PORT_CMD_SUD;

    // activate link
    fRegs->cmd = (fRegs->cmd & ~PORT_CMD_ICC_MASK) | PORT_CMD_ICC_ACTIVE;

    // enable FIS receive
    fRegs->cmd |= PORT_CMD_FER;

    FlushPostedWrites();

    return B_OK;
}