int
main ()
{
  EFLAGS_TYPE flags = 0xD7; /* 111010111b  */

  __writeeflags (flags);

  flags = __readeflags ();

  if ((flags & 0xFF) != 0xD7)
    abort ();

#ifdef DEBUG
    printf ("PASSED\n");
#endif

  return 0;
}