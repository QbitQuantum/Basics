PRIVATE Pointer si_readDouble (char *buffer, boolean *error)
{
    double value;

#ifdef MACINTOSH
    value = ATOF(buffer);
    *error = FALSE;
#else
    *error = (sscanf (buffer, "%lf", (double *) &value) != 1);
#endif
    return SUIT_copyData ((void *) &value, sizeof (double));
}