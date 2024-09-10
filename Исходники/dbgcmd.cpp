unsigned find2dlg(unsigned start)
{
   static unsigned code = 0xF3, mask = 0xFF; char ln[64];
   filledframe(10,10,16,5);
   tprint(10,10,"   find data    ", FRM_HEADER);
   sprintf(ln, "code: %08X", _byteswap_ulong(code)); tprint(11,12,ln, FFRAME_INSIDE);
   sprintf(ln, "mask: %08X", _byteswap_ulong(mask)); tprint(11,13,ln, FFRAME_INSIDE);
   sprintf(str, "%08X", _byteswap_ulong(code));
   if (!inputhex(17,12,8,true)) return -1;
   sscanf(str, "%x", &code); code = _byteswap_ulong(code);
   tprint(17,12,str, FFRAME_INSIDE);
   sprintf(str, "%08X", _byteswap_ulong(mask));
   if (!inputhex(17,13,8,true)) return -1;
   sscanf(str, "%x", &mask); mask = _byteswap_ulong(mask);
   unsigned i; //Alone Coder 0.36.7
   for (unsigned ptr = memadr(start+1); ptr != start; ptr = memadr(ptr+1)) {
      unsigned char *cd = (unsigned char*)&code, *ms = (unsigned char*)&mask;
      for (/*unsigned*/ i = 0; i < 4; i++)
         if ((editrm(memadr(ptr+i)) & ms[i]) != (cd[i] & ms[i])) break;
      if (i == 4) return ptr;
   }
   tprint(11,12,"  not found   ", FFRAME_ERROR);
   tprint(11,13,"              ", FFRAME_ERROR);
   debugflip();
   while (!process_msgs());
   return -1;
}