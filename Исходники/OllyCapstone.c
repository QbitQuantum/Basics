ulong cdecl NewDisasm(ulong nOldDisasmSize, uchar *src, ulong srcsize,
					  ulong srcip, uchar *srcdec,
					  t_disasm *disasm,int disasmmode,ulong threadid)
{
	uint16_t i;
	unsigned int j;
	cs_insn *insn;
	size_t count;
	char base_str_lowercase[] = "0123456789abcdef";
	char base_str_uppercase[] = "0123456789ABCDEF";
	char *p;
	ulong nsize = nOldDisasmSize;

	if (g_EnableOllyCapstone == 0)
		return nsize;

	if (*g_pDisasmLowercase)
		p = base_str_lowercase;
	else
		p = base_str_uppercase;

	count = cs_disasm(g_cshHandle, src, srcsize, srcip, 1, &insn);
	if (count != 1)
	{
		
		fpAddToList(0, 1, "[%s error] cs_disasm(): %s.", OLLY_CAPSTONE_NAME, 
			cs_strerror(cs_errno(g_cshHandle)));
		
		return nsize; /*using result from Olly */
	}
	else
	{
		if (disasm == NULL)
		{
			cs_free(insn, count);
			return nsize;
		}

		switch(disasmmode & DISASM_MODE) /* extract disassembling mode */
		{
		case DISASM_DATA:
		case DISASM_TRACE:
		case DISASM_FILE:
		case DISASM_CODE:
		case DISASM_ALL:
		case DISASM_RTRACE:

			for (j = 0, i = 0; i < insn->size && j < TEXTLEN-2; ++i)
			{
				disasm->dump[j++] = p[insn->bytes[i] >> 4 ];
				disasm->dump[j++] = p[insn->bytes[i] & 0xf];
			}
			disasm->dump[j] = '\0';

			strcpy_s(disasm->result, TEXTLEN, insn->mnemonic);
			strcat_s(disasm->result, TEXTLEN, " ");
			strcat_s(disasm->result, TEXTLEN, insn->op_str);

			if (!(*g_pDisasmLowercase))
			{
				p = disasm->result;
				while (*p)
					*p++ = (char)toupper(*p);
			}

		case DISASM_SIZE: /* Determine command size only */
			nsize = insn->size;
			break;
		default:
			break;
		}

		cs_free(insn, count);
	}

	return nsize;
}