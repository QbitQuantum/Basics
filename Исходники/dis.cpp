std::string DisassembleMIPS(u32 PC, u32 instr)
{
 std::string ret = "UNKNOWN";
 unsigned int rs = (instr >> 21) & 0x1F;
 unsigned int rt = (instr >> 16) & 0x1F;
 unsigned int rd = (instr >> 11) & 0x1F;
 unsigned int shamt = (instr >> 6) & 0x1F;
 unsigned int immediate = (s32)(s16)(instr & 0xFFFF);
 unsigned int immediate_ze = (instr & 0xFFFF);
 unsigned int jt = instr & ((1 << 26) - 1);

 static const char *gpr_names[32] =
 {
  "r0", "at", "v0", "v1", "a0", "a1", "a2", "a3", "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7",
    "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7", "t8", "t9", "k0", "k1", "gp", "sp", "fp", "ra"
 };

 OpEntry *op = ops;

 while(op->mnemonic)
 {
  if((instr & op->mask) == op->value)
  {
   // a = shift amount
   // s = rs
   // t = rt
   // d = rd
   // i = immediate
   // z = immediate, zero-extended
   // p = PC + 4 + immediate
   // P = ((PC + 4) & 0xF0000000) | (26bitval << 2)
   char s_a[16];
   char s_i[16];
   char s_z[16];
   char s_p[16];
   char s_P[16];
	 char s_D[16];

	_snprintf(s_D, sizeof(s_D), "%d", rd);

   _snprintf(s_a, sizeof(s_a), "%d", shamt);

   if(immediate < 0)
    _snprintf(s_i, sizeof(s_i), "%d", immediate);
   else
    _snprintf(s_i, sizeof(s_i), "0x%04x", (u32)immediate);

   _snprintf(s_z, sizeof(s_z), "0x%04x", immediate_ze);

   _snprintf(s_p, sizeof(s_p), "0x%08x", PC + 4 + (immediate << 2));

   _snprintf(s_P, sizeof(s_P), "0x%08x", ((PC + 4) & 0xF0000000) | (jt << 2));

   ret = std::string(op->mnemonic);
   ret.append(10 - ret.size(), ' ');

   for(unsigned int i = 0; i < strlen(op->format); i++)
   {
    switch(op->format[i])
    {
     case 'a':
	ret.append(s_a);
	break;

     case 'i':
	ret.append(s_i);
	break;

     case 'z':
	ret.append(s_z);
	break;

     case 'p':
	ret.append(s_p);
	break;

     case 'P':
	ret.append(s_P);
	break;

     case 's':
	ret.append(gpr_names[rs]);
	break;

     case 't':
	ret.append(gpr_names[rt]);
	break;

    case 'd':
	ret.append(gpr_names[rd]);
	break;

		case 'D':
			ret.append(s_D);
			break;

     default:
	ret.append(1, op->format[i]);
	break;
    }
   }
   break;
  }
  op++;
 }

 return(ret);
}