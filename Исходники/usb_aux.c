static bool
usb_setup(setup_t *sp)
{
  switch(sp->reqtype.type)
  {
    case 0x00: PUTS("usb: std_req - "); return std_req(sp); break;
    case 0x01: PUTS("usb: class_req - "); break;
    case 0x02: PUTS("usb: vendor_req - "); break;
    default:   GDB2_PUTS("unknown req - "); STALLEP0();
  }

  GDB2_PUTS(".\n");
  return false;
}