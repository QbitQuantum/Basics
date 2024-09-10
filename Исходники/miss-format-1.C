void
bar (const char *fmt, ...)
{
  va_list ap;
  va_start (ap, fmt);
  vscanf (fmt, ap); /* { dg-warning "candidate" "scanf attribute warning" { xfail *-*-vxworks* } } */
  va_end (ap);
}