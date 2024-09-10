    8,	/* 8 bits in a byte  */		\
    bfd_arch_arc,			\
    mach,				\
    "arc",				\
    print_name,				\
    4, /* section alignment power  */	\
    default_p,				\
    bfd_default_compatible,		\
    bfd_default_scan,			\
    bfd_arch_default_fill,		\
    next,				\
  }

static const bfd_arch_info_type arch_info_struct[] =
{
  ARC (bfd_mach_arc_arc600, "ARC600", FALSE, &arch_info_struct[1]),
  ARC (bfd_mach_arc_arc600, "A6"    , FALSE, &arch_info_struct[2]),
  ARC (bfd_mach_arc_arc601, "ARC601", FALSE, &arch_info_struct[3]),
  ARC (bfd_mach_arc_arc700, "ARC700", FALSE, &arch_info_struct[4]),
  ARC (bfd_mach_arc_arc700, "A7",     FALSE, &arch_info_struct[5]),
  ARC (bfd_mach_arc_arcv2,  "ARCv2",  FALSE, &arch_info_struct[6]),
  ARC (bfd_mach_arc_arcv2,  "EM",     FALSE, &arch_info_struct[7]),
  ARC (bfd_mach_arc_arcv2,  "HS",     FALSE, NULL),
};

const bfd_arch_info_type bfd_arc_arch =
  ARC (bfd_mach_arc_arcv2,  "HS", TRUE, &arch_info_struct[0]);

/* Utility routines.  */

/* Given cpu type NAME, return its bfd_mach_arc_xxx value.