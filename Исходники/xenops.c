static void *
atop(const char *a)
{
#ifdef AMD64
    return (void *)_atoi64(a);
#else
    return (void *)atoi(a);
#endif
}