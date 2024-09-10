 void
fpinit_ASL(void)
{
	static int first = 1;

#ifndef No_Control87 /* for DEC Alpha */
#ifndef MCW_EM
#ifndef _MCW_EM	/* for cygwin with -mno-cygwin */
#define _MCW_EM 0x0008001F
#endif
#define MCW_EM _MCW_EM
#endif
#ifndef PC_53
#ifndef _PC_53
#define _PC_53 0x00010000
#endif
#define PC_53 _PC_53
#endif
#ifndef MCW_PC
#ifndef _MCW_PC
#define _MCW_PC 0x00030000
#endif
#define MCW_PC _MCW_PC
#endif
	_control87(MCW_EM | PC_53, MCW_EM | MCW_PC);
#endif
	if (first) {
		first = 0;
		siglisten();
		}
	}