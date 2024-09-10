char peek (FILE * f)
{
    char c = fgetc (f);
    ungetc (c, f);
    return c;
}