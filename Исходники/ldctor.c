static int
ctor_prio (const char *name)
{
  /* The name will look something like _GLOBAL_$I$65535$test02__Fv.
     There might be extra leading underscores, and the $ characters
     might be something else.  The I might be a D.  */

  while (*name == '_')
    ++name;

  if (! CONST_STRNEQ (name, "GLOBAL_"))
    return -1;

  name += sizeof "GLOBAL_" - 1;

  if (name[0] != name[2])
    return -1;
  if (name[1] != 'I' && name[1] != 'D')
    return -1;
  if (! ISDIGIT (name[3]))
    return -1;

  return atoi (name + 3);
}