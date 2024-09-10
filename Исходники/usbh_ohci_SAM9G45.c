void usbh_ohci_hw_delay_ms (U32 ms) {

  ms <<= 12;
  while (ms--) {
    __nop(); __nop(); __nop();
  }
}