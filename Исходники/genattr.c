static void
gen_attr (rtx attr)
{
  const char *p, *tag;
  int is_const = GET_CODE (XEXP (attr, 2)) == CONST;

  printf ("#define HAVE_ATTR_%s\n", XSTR (attr, 0));

  /* If numeric attribute, don't need to write an enum.  */
  p = XSTR (attr, 1);
  if (*p == '\0')
    printf ("extern int get_attr_%s (%s);\n", XSTR (attr, 0),
            (is_const ? "void" : "rtx"));
  else
    {
      printf ("enum attr_%s {", XSTR (attr, 0));

      while ((tag = scan_comma_elt (&p)) != 0)
        {
          write_upcase (XSTR (attr, 0));
          putchar ('_');
          while (tag != p)
            putchar (TOUPPER (*tag++));
          if (*p == ',')
            fputs (", ", stdout);
        }

      fputs ("};\n", stdout);
      printf ("extern enum attr_%s get_attr_%s (%s);\n\n",
              XSTR (attr, 0), XSTR (attr, 0), (is_const ? "void" : "rtx"));
    }

  /* If `length' attribute, write additional function definitions and define
     variables used by `insn_current_length'.  */
  if (! strcmp (XSTR (attr, 0), "length"))
    {
      puts ("\
extern void shorten_branches (rtx);\n\
extern int insn_default_length (rtx);\n\
extern int insn_min_length (rtx);\n\
extern int insn_variable_length_p (rtx);\n\
extern int insn_current_length (rtx);\n\n\
#include \"insn-addr.h\"\n");
    }