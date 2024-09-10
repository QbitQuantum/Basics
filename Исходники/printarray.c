/* ceil_DIV(a,b) :=  ceil(a / b)  in _int_ arithmetic : */
static R_INLINE
int ceil_DIV(int a, int b)
{
    div_t div_res = div(a, b);
    return div_res.quot + ((div_res.rem != 0) ? 1 : 0);
}