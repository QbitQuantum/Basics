long double TSolver::calc(const char f,const long double a,const long double b) //calculates function
{switch (f)
   {case '+' : return a+b;
    case '-' : return a-b;
    case '*' : return a*b;
    case '/' : if (b==0) {Err=E_DEV_ZERO;return 0;};return a/b;
    case '!' : if (floorl(a)!=a) {Err=E_ARG;return 0;}return factor(a);
    case '_' : return -a;

    case cpi   : return M_PI;
    case cx    : return X;

    case fexp  : return exp(a);
    case fln   : if (a<0) {Err=E_ARG;return 0;}return logl(a);
    case flog  : if (a<0) {Err=E_ARG;return 0;}return log10l(a);
    case flogn : if (a<0) {Err=E_ARG;return 0;}return log(a)/log(b);

    case '^':
    case f_op_pow:
    case fpow  : if (a<0 && b<1 && b>0 && (!fmodl(b,2))) {Err=E_ARG;return 0;}return powl(a,b);
    case fsqr  : return a*a;
    case f_op_root:
    case froot : if (a<0 && (!fmodl(b,2))){Err=E_ARG;return 0;}
                   return (a>0 || (!fmodl(b,2)))?powl(a,1/b):-powl(-a,1/b);
    case fsqrt : if (a<0) {Err=E_ARG;return 0;}return sqrtl(a);
    case f_abs  : return fabsl(a);

    case fsin  : return sinl(a);
    case fcos  : return cosl(a);
    case ftan  : if (a==M_PI_2 || a==(M_PI_2+M_PI)) {Err=E_ARG;return 0;} return tanl(a);
    case fctan : if (a==0 || a==M_PI) {Err=E_ARG;return 0;} return 1/tanl(a);

    case fsin+ARC : if (fabsl(a)>1) {Err=E_ARG;return 0;} return asinl(a);
    case fcos+ARC : if (fabsl(a)>1) {Err=E_ARG;return 0;} return acosl(a);
    case ftan+ARC : return atanl(a);
    case fctan+ARC: return atanl(1/a);

    case fsin+HYP : return sinhl(a);
    case fcos+HYP : return coshl(a);
    case ftan+HYP : return tanhl(a);
    case fctan+HYP : return 1/tanhl(a);
#ifndef _OLD_
    case fsin+HYP+ARC : return asinhl(a);
    case fcos+HYP+ARC : return acoshl(a);
    case ftan+HYP+ARC : if (fabsl(a)>=1) {Err=E_ARG;return 0;} return atanhl(a);
    case fctan+HYP+ARC : if (a==0 ) {Err=E_ARG;return 0;} return atanhl(1/a);
#endif
    default: return 0;
   }
}