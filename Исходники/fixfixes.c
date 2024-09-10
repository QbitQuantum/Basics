/*
 *  Emit the GNU standard type wrapped up in such a way that
 *  this thing can be encountered countless times during a compile
 *  and not cause even a warning.
 */
static const char*
emit_gnu_type (const char* text, regmatch_t* rm )
{
  char z_TYPE[ 64 ];
  char z_type[ 64 ];

  fwrite (text, rm[0].rm_so, 1, stdout);

  {
    const char* ps = text   + rm[1].rm_so;
    const char* pe = text   + rm[1].rm_eo;
    char* pd = z_type;
    char* pD = z_TYPE;

    while (ps < pe)
      *(pD++) = TOUPPER( *(pd++) = *(ps++) );

    *pD = *pd = NUL;
  }

  /*
   *  Now print out the reformed typedef,
   *  with a C++ guard for WCHAR
   */
  {
    tSCC z_fmt[] = "\
#if !defined(_GCC_%s_T)%s\n\
#define _GCC_%s_T\n\
typedef __%s_TYPE__ %s_t;\n\
#endif\n";

    const char *const pz_guard = (strcmp (z_type, "wchar") == 0)
                           ? " && ! defined(__cplusplus)" : "";

    printf (z_fmt, z_TYPE, pz_guard, z_TYPE, z_TYPE, z_type);
  }

  return text += rm[0].rm_eo;
}