int
opt_vscanf (Opt o, const char *fmt, va_list ap)
{
    ListIterator itr;
    char *item;
    int ret = 0;

    NP_ASSERT (o->magic == OPT_MAGIC);

    if (!(itr = list_iterator_create (o->list)))
        msg_exit ("out of memory");
    while ((item = list_next (itr))) {
        va_list vacpy;

        va_copy (vacpy, ap);
        ret = vsscanf (item, fmt, vacpy);
        va_end (vacpy);

        if (ret > 0)
            break;
    }
    list_iterator_destroy (itr);
    return ret;
}