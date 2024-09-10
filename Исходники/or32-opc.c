static unsigned long
insn_extract (char param_ch, char *enc_initial)
{
  char *enc;
  unsigned long ret = 0;
  unsigned opc_pos = 32;

  for (enc = enc_initial; *enc != '\0'; )
    if ((*enc == '0') && (*(enc + 1) == 'x')) 
      {
	unsigned long tmp = strtol (enc+2, NULL, 16);

        opc_pos -= 4;
	if (param_ch == '0' || param_ch == '1')
	  {
	    if (param_ch == '0')
	      tmp = 15 - tmp;
	    ret |= tmp << opc_pos;
	  }
        enc += 3;
      }
    else
      {
	if (*enc == '0' || *enc == '1' || *enc == '-' || ISALPHA (*enc))
	  {
	    opc_pos--;
	    if (param_ch == *enc)
	      ret |= 1 << opc_pos;
	  }
	enc++;
      }
  return ret;
}