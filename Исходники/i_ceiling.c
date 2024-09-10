integer i_sceiling(real *x)
#endif
{
#define CEIL(x) ((int)(x) + ((x) > 0 && (x) != (int)(x)))

    return (integer) CEIL(*x);
}