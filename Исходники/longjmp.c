int
call_longjmp (jmp_buf *buf)
{
  longjmps++;
  longjmp (*buf, 1);
}