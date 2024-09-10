static unsigned long
get_ds_base (void)
{
  unsigned short dsval;
  LDT_ENTRY ldt;
  unsigned long dsbase;

  __asm
    {
      mov dsval,ds
    }

  dsbase = 0;

  GetThreadSelectorEntry (GetCurrentThread(), dsval, &ldt);

  dsbase = ldt.HighWord.Bits.BaseHi << 24 | ldt.HighWord.Bits.BaseMid << 16
	     | ldt.BaseLow;

  return dsbase;
}