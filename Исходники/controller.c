// Copies data from the the PI into RDRAM.
static int pi_dma_write(struct pi_controller *pi) {
  uint32_t dest = pi->regs[PI_DRAM_ADDR_REG] & 0x7FFFFF;
  uint32_t source = pi->regs[PI_CART_ADDR_REG] & 0xFFFFFFF;
  uint32_t length = (pi->regs[PI_WR_LEN_REG] & 0xFFFFFF) + 1;

  if (length & 7)
    length = (length + 7) & ~7;

  if (pi->bus->dd->ipl_rom && (source & 0x06000000) == 0x06000000) {
    source &= 0x003FFFFF;

    if (source + length > 0x003FFFFF)
      length = 0x003FFFFF - source;

    memcpy(pi->bus->ri->ram + dest, pi->bus->dd->ipl_rom + source, length);
  }

  else if ((source & 0x05000000) == 0x05000000)
    dd_dma_write(pi->bus->dd, source, dest, length);

  // SRAM and FlashRAM
  else if (source >= 0x08000000 && source < 0x08010000) {
    uint32_t addr = source & 0x00FFFFF;

    if (pi->sram->ptr != NULL && addr + length <= 0x8000)
      memcpy(pi->bus->ri->ram + dest, pi->sram->ptr + addr, length);

    else if (pi->flashram.data != NULL) {
      // SRAM
      if (pi->flashram.mode == FLASHRAM_STATUS) {
        uint64_t status = htonll(pi->flashram.status);
        memcpy(pi->bus->ri->ram + dest, &status, 8);
      }

      // FlashRAM
      else if (pi->flashram.mode == FLASHRAM_READ)
        memcpy(pi->bus->ri->ram + dest, pi->flashram.data + addr * 2, length);
    }
  }

  else if (source >= 0x18000000 && source < 0x18400000) {
    // TODO: 64DD modem
  }

  else if (pi->rom) {
    if (source + length > pi->rom_size) {
      length = pi->rom_size - source;
      //assert(0);
    }

    // TODO: Very hacky.
    if (source < pi->rom_size)
      memcpy(pi->bus->ri->ram + dest, pi->rom + source, length);
  }

  return 0;
}