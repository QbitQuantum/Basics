void FPGARegisters::print_register_values() {
  printf("==============================\n");
  printf("Print %d FPGA Registers starting at: Ox%08X\n", size_/4, dev_base_);
  printf("Offset  Hex         Int\n");
  for(int i = 0; i < size_; i+=4)
  {
    printf("0x%04X: 0x%08X  %d\n", i, getRegisterValue(i), getRegisterValue(i));
  }
  printf("==============================\n");
}