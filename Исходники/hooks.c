static int my_putw(int w, FILE *fp)
{
    return putw(w, _get_actual_fp(fp));
}