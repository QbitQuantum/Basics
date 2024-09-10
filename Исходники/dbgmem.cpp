char dispatch_mem()
{
   Z80 &cpu = CpuMgr.Cpu();
   if (!mem_max)
       return 0;
   if (mem_ascii)
   {
      u8 Kbd[256];
      GetKeyboardState(Kbd);
      unsigned short k;
      if (ToAscii(input.lastkey,0,Kbd,&k,0) != 1)
          return 0;
      k &= 0xFF;
      if (k < 0x20 || k >= 0x80)
          return 0;
      editwm(cpu.mem_curs, (unsigned char)k);
      mright();
      return 1;
   }
   else
   {
      if ((input.lastkey >= '0' && input.lastkey <= '9') || (input.lastkey >= 'A' && input.lastkey <= 'F'))
      {
         unsigned char k = (input.lastkey >= 'A') ? input.lastkey-'A'+10 : input.lastkey-'0';
         unsigned char c = editrm(cpu.mem_curs);
         if (cpu.mem_second) editwm(cpu.mem_curs, (c & 0xF0) | k);
         else editwm(cpu.mem_curs, (c & 0x0F) | (k << 4));
         mright();
         return 1;
      }
   }
   return 0;
}