double
SDL_scalbn(double x, int n)
{
#if defined(HAVE_SCALBN)
    return scalbn(x, n);
#else
    return SDL_uclibc_scalbn(x, n);
#endif /* HAVE_SCALBN */
}