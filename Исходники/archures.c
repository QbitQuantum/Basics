bfd_boolean
bfd_default_scan (const bfd_arch_info_type *info, const char *string)
{
  const char *ptr_src;
  const char *ptr_tst;
  unsigned long number;
  enum bfd_architecture arch;
  const char *printable_name_colon;

  /* Exact match of the architecture name (ARCH_NAME) and also the
     default architecture?  */
  if (strcasecmp (string, info->arch_name) == 0
      && info->the_default)
    return TRUE;

  /* Exact match of the machine name (PRINTABLE_NAME)?  */
  if (strcasecmp (string, info->printable_name) == 0)
    return TRUE;

  /* Given that printable_name contains no colon, attempt to match:
     ARCH_NAME [ ":" ] PRINTABLE_NAME?  */
  printable_name_colon = strchr (info->printable_name, ':');
  if (printable_name_colon == NULL)
    {
      size_t strlen_arch_name = strlen (info->arch_name);
      if (strncasecmp (string, info->arch_name, strlen_arch_name) == 0)
	{
	  if (string[strlen_arch_name] == ':')
	    {
	      if (strcasecmp (string + strlen_arch_name + 1,
			      info->printable_name) == 0)
		return TRUE;
	    }
	  else
	    {
	      if (strcasecmp (string + strlen_arch_name,
			      info->printable_name) == 0)
		return TRUE;
	    }
	}
    }

  /* Given that PRINTABLE_NAME has the form: <arch> ":" <mach>;
     Attempt to match: <arch> <mach>?  */
  if (printable_name_colon != NULL)
    {
      size_t colon_index = printable_name_colon - info->printable_name;
      if (strncasecmp (string, info->printable_name, colon_index) == 0
	  && strcasecmp (string + colon_index,
			 info->printable_name + colon_index + 1) == 0)
	return TRUE;
    }

  /* Given that PRINTABLE_NAME has the form: <arch> ":" <mach>; Do not
     attempt to match just <mach>, it could be ambiguous.  This test
     is left until later.  */

  /* NOTE: The below is retained for compatibility only.  Please do
     not add to this code.  */

  /* See how much of the supplied string matches with the
     architecture, eg the string m68k:68020 would match the 68k entry
     up to the :, then we get left with the machine number.  */

  for (ptr_src = string, ptr_tst = info->arch_name;
       *ptr_src && *ptr_tst;
       ptr_src++, ptr_tst++)
    {
      if (*ptr_src != *ptr_tst)
	break;
    }

  /* Chewed up as much of the architecture as will match, skip any
     colons.  */
  if (*ptr_src == ':')
    ptr_src++;

  if (*ptr_src == 0)
    {
      /* Nothing more, then only keep this one if it is the default
	 machine for this architecture.  */
      return info->the_default;
    }

  number = 0;
  while (ISDIGIT (*ptr_src))
    {
      number = number * 10 + *ptr_src - '0';
      ptr_src++;
    }

  /* NOTE: The below is retained for compatibility only.
     PLEASE DO NOT ADD TO THIS CODE.  */

  switch (number)
    {
      /* FIXME: These are needed to parse IEEE objects.  */
      /* The following seven case's are here only for compatibility with
	 older binutils (at least IEEE objects from binutils 2.9.1 require
	 them).  */
    case bfd_mach_m68000:
    case bfd_mach_m68010:
    case bfd_mach_m68020:
    case bfd_mach_m68030:
    case bfd_mach_m68040:
    case bfd_mach_m68060:
    case bfd_mach_cpu32:
      arch = bfd_arch_m68k;
      break;
    case 68000:
      arch = bfd_arch_m68k;
      number = bfd_mach_m68000;
      break;
    case 68010:
      arch = bfd_arch_m68k;
      number = bfd_mach_m68010;
      break;
    case 68020:
      arch = bfd_arch_m68k;
      number = bfd_mach_m68020;
      break;
    case 68030:
      arch = bfd_arch_m68k;
      number = bfd_mach_m68030;
      break;
    case 68040:
      arch = bfd_arch_m68k;
      number = bfd_mach_m68040;
      break;
    case 68060:
      arch = bfd_arch_m68k;
      number = bfd_mach_m68060;
      break;
    case 68332:
      arch = bfd_arch_m68k;
      number = bfd_mach_cpu32;
      break;
    case 5200:
      arch = bfd_arch_m68k;
      number = bfd_mach_mcf_isa_a_nodiv;
      break;
    case 5206:
      arch = bfd_arch_m68k;
      number = bfd_mach_mcf_isa_a_mac;
      break;
    case 5307:
      arch = bfd_arch_m68k;
      number = bfd_mach_mcf_isa_a_mac;
      break;
    case 5407:
      arch = bfd_arch_m68k;
      number = bfd_mach_mcf_isa_b_nousp_mac;
      break;
    case 5282:
      arch = bfd_arch_m68k;
      number = bfd_mach_mcf_isa_aplus_emac;
      break;

    case 32000:
      arch = bfd_arch_we32k;
      break;

    case 3000:
      arch = bfd_arch_mips;
      number = bfd_mach_mips3000;
      break;

    case 4000:
      arch = bfd_arch_mips;
      number = bfd_mach_mips4000;
      break;

    case 6000:
      arch = bfd_arch_rs6000;
      break;

    case 7410:
      arch = bfd_arch_sh;
      number = bfd_mach_sh_dsp;
      break;

    case 7708:
      arch = bfd_arch_sh;
      number = bfd_mach_sh3;
      break;

    case 7729:
      arch = bfd_arch_sh;
      number = bfd_mach_sh3_dsp;
      break;

    case 7750:
      arch = bfd_arch_sh;
      number = bfd_mach_sh4;
      break;

    default:
      return FALSE;
    }

  if (arch != info->arch)
    return FALSE;

  if (number != info->mach)
    return FALSE;

  return TRUE;
}