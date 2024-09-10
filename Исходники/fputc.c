int fputc(int c, FILE *f)
{
    Wr$PutC(f->wr, c);
    return (int)((unsigned char)c);
}