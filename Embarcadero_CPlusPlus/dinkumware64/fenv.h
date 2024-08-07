/* fenv.h standard header -- simple version */
#ifndef _FENV
#define _FENV
#ifndef _YMATH
 #include <ymath.h>
#endif /* _YMATH */

_C_STD_BEGIN
_C_LIB_DECL

 #if _FPP_TYPE == _FPP_X86
typedef unsigned int fexcept_t;
typedef struct fenv_t
	{	/* FPP registers */
	fexcept_t _Fe_ctl, _Fe_stat, _Fe_pad[7];	/* extra padding for 64-bit */
	} fenv_t;

  #if defined(__APPLE__)
typedef struct _Fpp_state
	{	/* Apple FPP registers */
	unsigned short _Fe_ctl, _Fe_pad1, _Fe_stat, _Fe_pad2, _Fe_pad[7];
	} _Fpp_state;
  #endif /* defined(__APPLE__) */

_CRTIMP2 void _Fegetctl(fexcept_t *);
_CRTIMP2 void _Fesetctl(fexcept_t *);

  #define FE_DOWNWARD	0x01
  #define FE_TONEAREST	0x00
  #define FE_TOWARDZERO	0x03
  #define FE_UPWARD		0x02

  #define _FE_EXCEPT_OFF	0
  #define _FE_EXMASK_OFF	0
  #define _FE_RND_OFF		10

  #define _FE_AUTO_RAISE

  #if 1200 <= _MSC_VER
   #define _FE_EXMASK_ALL	0x127f	/* 53-bit precision for VC++ */

  #else /* _MSC_VER */
   #define _FE_EXMASK_ALL	0x137f	/* 64-bit precision otherwise */
  #endif /* _MSC_VER */

 #elif _FPP_TYPE == _FPP_SPARC
typedef unsigned long fexcept_t;
typedef unsigned long fenv_t;

  #define FE_DOWNWARD	0x03
  #define FE_TONEAREST	0x00
  #define FE_TOWARDZERO	0x01
  #define FE_UPWARD		0x02

  #define _FE_EXCEPT_OFF	5
  #define _FE_EXMASK_OFF	23
  #define _FE_RND_OFF		30

  #define _FE_EXLAST_OFF	0

 #elif _FPP_TYPE == _FPP_MIPS
typedef unsigned long fexcept_t;
typedef unsigned long fenv_t;

  #define FE_DOWNWARD	0x03
  #define FE_TONEAREST	0x00
  #define FE_TOWARDZERO	0x01
  #define FE_UPWARD		0x02

  #define _FE_EXCEPT_OFF	2
  #define _FE_EXMASK_OFF	7
  #define _FE_RND_OFF		0

  #define _FE_AUTO_RAISE
  #define _FE_EXLAST_OFF	12

 #elif _FPP_TYPE == _FPP_S390
typedef unsigned long fexcept_t;
typedef unsigned long fenv_t;

  #define FE_DOWNWARD	0x03
  #define FE_TONEAREST	0x00
  #define FE_TOWARDZERO	0x01
  #define FE_UPWARD		0x02

  #define _FE_EXCEPT_OFF	19
  #define _FE_EXMASK_OFF	27
  #define _FE_RND_OFF		30

 #elif _FPP_TYPE == _FPP_PPC
typedef unsigned long fexcept_t;
typedef unsigned long fenv_t;

  #define FE_DOWNWARD	0x03
  #define FE_TONEAREST	0x00
  #define FE_TOWARDZERO	0x01
  #define FE_UPWARD		0x02

  #define _FE_EXCEPT_OFF	25
  #define _FE_EXMASK_OFF	3
  #define _FE_RND_OFF		0

 #elif _FPP_TYPE == _FPP_HPPA
typedef unsigned long fexcept_t;
typedef struct fenv_t
	{	/* FPP registers */
	fexcept_t _Fe_stat, _Fe_pad[3];
	} fenv_t;

fexcept_t _Fegetstat(void);
fexcept_t _Fesetstat(fexcept_t, fexcept_t);

  #define FE_DOWNWARD	0x03
  #define FE_TONEAREST	0x00
  #define FE_TOWARDZERO	0x01
  #define FE_UPWARD		0x02

  #define _FE_EXCEPT_OFF	27
  #define _FE_EXMASK_OFF	0
  #define _FE_RND_OFF		9

 #elif _FPP_TYPE == _FPP_ALPHA
typedef unsigned long fexcept_t;
typedef unsigned long fenv_t;

fexcept_t _Fegettrapenable(fenv_t);
fexcept_t _Fegetstat(void);
fexcept_t _Fesetstat(fexcept_t, fexcept_t);

  #define FE_DOWNWARD	0x01
  #define FE_TONEAREST	0x02
  #define FE_TOWARDZERO	0x00
  #define FE_UPWARD		0x03

  #define _FE_EXCEPT_OFF	20
  #define _FE_EXMASK_OFF	17
  #define _FE_RND_OFF		26

  #define _FE_ALL_ENABLE	(((FE_INEXACT | FE_UNDERFLOW) << 10) \
	| FE_DIVBYZERO | FE_INVALID | FE_OVERFLOW)
  #define _FE_EXMASK_ALL	0x600e8000

 #elif _FPP_TYPE == _FPP_ARM
typedef unsigned long fexcept_t;
typedef unsigned long fenv_t;

  #define FE_DOWNWARD	0x02
  #define FE_TONEAREST	0x00
  #define FE_TOWARDZERO	0x03
  #define FE_UPWARD		0x01

  #define _FE_EXCEPT_OFF	0
  #define _FE_EXMASK_OFF	8
  #define _FE_RND_OFF		22

  #define _FE_EXMASK_ALL	0xff00

 #elif _FPP_TYPE == _FPP_M68K
typedef unsigned long fexcept_t;
typedef struct fenv_t
	{	/* FPP registers */
	fexcept_t _Fe_ctl, _Fe_stat, _Fe_addr;
	} fenv_t;

fexcept_t _Fegetstat(void);
fexcept_t _Fesetstat(fexcept_t, fexcept_t);

  #define FE_DOWNWARD	0x02
  #define FE_TONEAREST	0x00
  #define FE_TOWARDZERO	0x01
  #define FE_UPWARD		0x03

  #define _FE_EXCEPT_OFF	3
  #define _FE_EXMASK_OFF	9
  #define _FE_RND_OFF		4

  #define _FE_EXLAST_OFF	9

 #elif _FPP_TYPE == _FPP_SH4
typedef unsigned long fexcept_t;
typedef unsigned long fenv_t;

  #define FE_DOWNWARD	0x03
  #define FE_TONEAREST	0x00
  #define FE_TOWARDZERO	0x01
  #define FE_UPWARD		0x02

  #define _FE_EXCEPT_OFF	2
  #define _FE_EXMASK_OFF	7
  #define _FE_RND_OFF		0

  #define _FE_AUTO_RAISE
  #define _FE_EXLAST_OFF	12
  #define _FE_EXMASK_ALL	0x80000

 #elif _FPP_TYPE == _FPP_IA64
typedef unsigned long fexcept_t;
typedef unsigned long fenv_t;

  #define FE_DOWNWARD	0x01
  #define FE_TONEAREST	0x00
  #define FE_TOWARDZERO	0x03
  #define FE_UPWARD		0x02

  #define _FE_EXCEPT_OFF	0
  #define _FE_EXMASK_OFF	13
  #define _FE_RND_OFF		10

  #define _FE_AUTO_RAISE

 #elif _FPP_TYPE == _FPP_WIN
typedef unsigned int fexcept_t;
typedef struct fenv_t
	{	/* FPP registers */
	fexcept_t _Fe_ctl, _Fe_stat;
	} fenv_t;

_CRTIMP2 unsigned int _controlfp(unsigned int,unsigned int);
_CRTIMP2 unsigned int _statusfp(void);
_CRTIMP2 unsigned int _clearfp(void);

_CRTIMP2 void _Fegetctl(fexcept_t *);
_CRTIMP2 void _Fesetctl(fexcept_t *);

#if defined(__CODEGEARC__)

#if defined(_WIN64)

// Thes are setup based on x86 flags and converted internally

#define FE_DOWNWARD	0x01
  #define FE_TONEAREST	0x00
  #define FE_TOWARDZERO	0x03
  #define FE_UPWARD	0x02

  #define _FE_EXCEPT_OFF	0
  #define _FE_EXMASK_OFF	0
  #define _FE_RND_OFF		10

  #define _FE_AUTO_RAISE

#define _FE_EXMASK_ALL	0x127f  // FIXME: strip precision?

//#define _FE_EXMASK_ALL	0x1F80

#else
#error Incorrect FP setup
#endif

#else
  #define FE_DOWNWARD	0x01
  #define FE_TONEAREST	0x00
  #define FE_TOWARDZERO	0x03
  #define FE_UPWARD		0x02

  #define _FE_EXCEPT_OFF	0
  #define _FE_EXMASK_OFF	0
  #define _FE_RND_OFF		8

  #define _FE_AUTO_RAISE
  #define _FE_EXMASK_ALL	0x000f
#endif

 #else /* _FPP_TYPE == _FPP_NONE or unknown */
typedef unsigned short fexcept_t;
typedef struct fenv_t
	{	/* FPP registers */
	fexcept_t _Fe_ctl, _Fe_stat;
	} fenv_t;

  #define FE_DOWNWARD	0x01
  #define FE_TONEAREST	0x00
  #define FE_TOWARDZERO	0x03
  #define FE_UPWARD		0x02

  #define _FE_EXCEPT_OFF	0
  #define _FE_EXMASK_OFF	0
  #define _FE_RND_OFF		10

  #define _FE_AUTO_RAISE

extern fenv_t _TLS_QUAL _Fenv;
 #endif /* _FPP_TYPE */

		/* MACROS */
#define FE_DIVBYZERO	_FE_DIVBYZERO
#define FE_INEXACT		_FE_INEXACT
#define FE_INVALID		_FE_INVALID
#define FE_OVERFLOW		_FE_OVERFLOW
#define FE_UNDERFLOW	_FE_UNDERFLOW
#define FE_ALL_EXCEPT	(FE_DIVBYZERO | FE_INEXACT \
	| FE_INVALID | FE_OVERFLOW | FE_UNDERFLOW)

#define _FE_RND_MASK	0x03u

#define FE_DFL_ENV	(&_CSTD _Fenv0)

		/* FUNCTION DECLARATIONS */
_CRTIMP2 int feclearexcept(int);
_CRTIMP2 int fegetexceptflag(fexcept_t *, int);
_CRTIMP2 int feraiseexcept(int);
_CRTIMP2 int fesetexceptflag(const fexcept_t *, int);
_CRTIMP2 int fetestexcept(int);
_CRTIMP2 int fegetround(void);
_CRTIMP2 int fesetround(int);
_CRTIMP2 int fegetenv(fenv_t *);
_CRTIMP2 int feholdexcept(fenv_t *);
_CRTIMP2 int fesetenv(const fenv_t *);
_CRTIMP2 int feupdateenv(const fenv_t *);

 #if _ADDED_C_LIB
_CRTIMP2 fexcept_t fegettrapenable(void);
_CRTIMP2 int fesettrapenable(fexcept_t);
 #endif /* _ADDED_C_LIB */

double _Force_raise(int except);

		/* OBJECT DECLARATIONS */
_EXTERN_CONST_DECL fenv_t _Fenv0;
_END_C_LIB_DECL
_C_STD_END
#endif /* _FENV */

#ifdef _STD_USING
using _CSTD fenv_t; using _CSTD fexcept_t;
using _CSTD feclearexcept; using _CSTD fegetexceptflag;
using _CSTD feraiseexcept; using _CSTD fesetexceptflag;
using _CSTD fetestexcept; using _CSTD fegetround;
using _CSTD fesetround; using _CSTD fegetenv;
using _CSTD feholdexcept; using _CSTD fesetenv;
using _CSTD feupdateenv;

 #if _ADDED_C_LIB
using _CSTD fegettrapenable; using _CSTD fesettrapenable;
 #endif /* _ADDED_C_LIB */

#endif /* _STD_USING */

/*
 * Copyright (c) by P.J. Plauger. All rights reserved.
 * Consult your license regarding permissions and restrictions.
V8.03a/17:1422 */
