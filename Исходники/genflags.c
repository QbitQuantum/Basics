/* Print out a wrapper macro for a function which corrects the number
   of arguments it takes.  Any missing arguments are assumed to be at
   the end.  */
static void
gen_macro (const char *name, int real, int expect)
{
  int i;

  gcc_assert (real <= expect);
  gcc_assert (real);

  /* #define GEN_CALL(A, B, C, D) gen_call((A), (B)) */
  fputs ("#define GEN_", stdout);
  for (i = 0; name[i]; i++)
    putchar (TOUPPER (name[i]));

  putchar('(');
  for (i = 0; i < expect - 1; i++)
    printf ("%c, ", i + 'A');
  printf ("%c) gen_%s (", i + 'A', name);

  for (i = 0; i < real - 1; i++)
    printf ("(%c), ", i + 'A');
  printf ("(%c))\n", i + 'A');
}