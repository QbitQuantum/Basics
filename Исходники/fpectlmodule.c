static void fpe_reset(Sigfunc *handler)
{
    /* Reset the exception handling machinery, and reset the signal
     * handler for SIGFPE to the given handler.
     */

/*-- SunOS and Solaris ----------------------------------------------------*/
#if defined(sun)
    /* References: ieee_handler, ieee_sun, ieee_functions, and ieee_flags
       man pages (SunOS or Solaris)
       cc -c -I/usr/local/python/include fpectlmodule.c
       ld -G -o fpectlmodule.so -L/opt/SUNWspro/lib fpectlmodule.o -lsunmath -lm
     */
#include <math.h>
#ifndef _SUNMATH_H
    extern void nonstandard_arithmetic(void);
    extern int ieee_flags(const char*, const char*, const char*, char **);
    extern long ieee_handler(const char*, const char*, sigfpe_handler_type);
#endif

    char *mode="exception", *in="all", *out;
    (void) nonstandard_arithmetic();
    (void) ieee_flags("clearall",mode,in,&out);
    (void) ieee_handler("set","common",(sigfpe_handler_type)handler);
    PyOS_setsig(SIGFPE, handler);

/*-- HPUX -----------------------------------------------------------------*/
#elif defined(__hppa) || defined(hppa)
    /* References:   fpsetmask man page */
    /* cc -Aa +z -c -I/usr/local/python/include fpectlmodule.c */
    /* ld -b -o fpectlmodule.sl fpectlmodule.o -lm */
#include <math.h>
    fpsetdefaults();
    PyOS_setsig(SIGFPE, handler);

/*-- IBM AIX --------------------------------------------------------------*/
#elif defined(__AIX) || defined(_AIX)
    /* References:   fp_trap, fp_enable man pages */
#include <fptrap.h>
    fp_trap(FP_TRAP_SYNC);
    fp_enable(TRP_INVALID | TRP_DIV_BY_ZERO | TRP_OVERFLOW);
    PyOS_setsig(SIGFPE, handler);

/*-- DEC ALPHA LINUX ------------------------------------------------------*/
#elif defined(__alpha) && defined(linux)
#include <asm/fpu.h>
    unsigned long fp_control =
    IEEE_TRAP_ENABLE_INV | IEEE_TRAP_ENABLE_DZE | IEEE_TRAP_ENABLE_OVF;
    ieee_set_fp_control(fp_control);
    PyOS_setsig(SIGFPE, handler);

/*-- Cray Unicos ----------------------------------------------------------*/
#elif defined(cray)
    /* UNICOS delivers SIGFPE by default, but no matherr */
#ifdef HAS_LIBMSET
    libmset(-1);
#endif
    PyOS_setsig(SIGFPE, handler);

/*-- FreeBSD ----------------------------------------------------------------*/
#elif defined(__FreeBSD__)
    fpresetsticky(fpgetsticky());
    fpsetmask(FP_X_INV | FP_X_DZ | FP_X_OFL);
    PyOS_setsig(SIGFPE, handler);

/*-- Linux ----------------------------------------------------------------*/
#elif defined(linux)
#ifdef __GLIBC__
#include <fpu_control.h>
#else
#include <i386/fpu_control.h>
#endif
#ifdef _FPU_SETCW
    {
        fpu_control_t cw = 0x1372;
        _FPU_SETCW(cw);
    }
#else
    __setfpucw(0x1372);
#endif
    PyOS_setsig(SIGFPE, handler);

/*-- Microsoft Windows, NT ------------------------------------------------*/
#elif defined(_MSC_VER)
    /* Reference: Visual C++ Books Online 4.2,
       Run-Time Library Reference, _control87, _controlfp */
#include <float.h>
    unsigned int cw = _EM_INVALID | _EM_ZERODIVIDE | _EM_OVERFLOW;
    (void)_controlfp(0, cw);
    PyOS_setsig(SIGFPE, handler);

/*-- Give Up --------------------------------------------------------------*/
#else
    fputs("Operation not implemented\n", stderr);
#endif

}