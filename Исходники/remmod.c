float remquof ( float x, float y, int *quo)
{
      int			iclx,icly;                        /* classify results of x,y */
      int32_t		iquo;                             /* low 32 bits of integral quotient */
      int32_t		iscx, iscy, idiff;                /* logb values and difference */
      int			i;                                /* loop variable */
      float        absy,x1,y1,z;                     /* local floating-point variables */
      float        rslt;
      fenv_t        OldEnv;
      hexdouble     OldEnvironment;
      int           newexc;
    
      FEGETENVD ( OldEnvironment.d );
      FESETENVD ( 0.0 );
	  __NOOP;
	  __NOOP;

      OldEnv = OldEnvironment.i.lo;
      
      *quo = 0;                                       /* initialize quotient result */
      iclx = __fpclassifyf(x);
      icly = __fpclassifyf(y);
      if (likely((iclx & icly) >= FP_NORMAL))    {     /* x,y both nonzero finite case */
         x1 = __FABSF(x);                              /* work with absolute values */
         absy = __FABSF(y);
         iquo = 0;                                    /* zero local quotient */
         iscx = (int32_t) logbf(x1);                  /* get binary exponents */
         iscy = (int32_t) logbf(absy);
         idiff = iscx - iscy;                         /* exponent difference */
         if (idiff >= 0) {                            /* exponent of x1 >= exponent of y1 */
              if (idiff != 0) {                       /* exponent of x1 > exponent of y1 */
                   y1 = scalbnf(absy,-iscy);            /* scale |y| to unit binade */
                   x1 = scalbnf(x1,-iscx);              /* ditto for |x| */
                   for (i = idiff; i != 0; i--) {     /* begin remainder loop */
                        if ((z = x1 - y1) >= 0) {     /* nonzero remainder step result */
                            x1 = z;                   /* update remainder (x1) */
                            iquo += 1;                /* increment quotient */
                        }
                        iquo += iquo;                 /* shift quotient left one bit */
                        x1 += x1;                     /* shift (double) remainder */
                   }                                  /* end of remainder loop */
                   x1 = scalbnf(x1,iscy);               /* scale remainder to binade of |y| */
              }                                       /* remainder has exponent <= exponent of y */
              if (x1 >= absy) {                       /* last remainder step */
                   x1 -= absy;
                   iquo +=1;
              }                                       /* end of last remainder step */
         }                                            /* remainder (x1) has smaller exponent than y */
         if (likely( x1 < HugeFHalved.fval ))
            z = x1 + x1;                              /* double remainder, without overflow */
         else
            z = HugeF.fval;
         if ((z > absy) || ((z == absy) && ((iquo & 1) != 0))) {
              x1 -= absy;                             /* final remainder correction */
              iquo += 1;
         }
         if (x < 0.0)
              x1 = -x1;                               /* remainder if x is negative */
         iquo &= 0x0000007f;                          /* retain low 7 bits of integer quotient */
         if ((signbit(x) ^ signbit(y)) != 0)    /* take care of sign of quotient */
              iquo = -iquo;
         *quo = iquo;                                 /* deliver quotient result */
         rslt = x1;
         goto ret;
    }                                                 /* end of x,y both nonzero finite case */
    else if ((iclx <= FP_QNAN) || (icly <= FP_QNAN)) {
         rslt = x+y;                                  /* at least one NaN operand */
         goto ret;
    }
    else if ((iclx == FP_INFINITE)||(icly == FP_ZERO)) {    /* invalid result */
         rslt = nanf(REM_NAN);
            OldEnvironment.i.lo |= SET_INVALID;
            FESETENVD_GRP( OldEnvironment.d );
         goto ret;
    }
    else                                              /* trivial cases (finite REM infinite   */
         rslt = x;                                    /*  or  zero REM nonzero) with *quo = 0 */
  ret:
      FEGETENVD_GRP( OldEnvironment.d );
      newexc = OldEnvironment.i.lo & FE_ALL_EXCEPT;
      OldEnvironment.i.lo = OldEnv;
      if ((newexc & FE_INVALID) != 0)
            OldEnvironment.i.lo |= SET_INVALID;
      OldEnvironment.i.lo |=  newexc & ( FE_INEXACT | FE_DIVBYZERO | FE_UNDERFLOW | FE_OVERFLOW );
      FESETENVD_GRP( OldEnvironment.d );
      return rslt;
}