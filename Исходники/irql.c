VOID HalpEndSystemInterrupt(KIRQL Irql)
/*
 * FUNCTION: Enable all irqs with higher priority.
 */
{
  const USHORT mask[] =
  {
     0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
     0x0000, 0x0000, 0x0000, 0x0000, 0x8000, 0xc000, 0xe000, 0xf000,
     0xf800, 0xfc00, 0xfe00, 0xff00, 0xff80, 0xffc0, 0xffe0, 0xfff0,
     0xfff8, 0xfffc, 0xfffe, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
  };

  /* Interrupts should be disable while enabling irqs of both pics */
  _disable();

  pic_mask_intr.both &= mask[Irql];
  WRITE_PORT_UCHAR((PUCHAR)0x21, (UCHAR)(pic_mask.master|pic_mask_intr.master));
  WRITE_PORT_UCHAR((PUCHAR)0xa1, (UCHAR)(pic_mask.slave|pic_mask_intr.slave));

  /* restore ints */
  _enable();
}