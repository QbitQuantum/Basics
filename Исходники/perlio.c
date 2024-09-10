int      
PerlIO_flush(PerlIO *f)
{
 return Fflush(f);
}