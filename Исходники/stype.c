/* Alternative implementation for manglestr_default. Mangling is similar to the original
   except for a few subtle differences for example in templates:
    namespace foo {
      template<class T> class bar {};
      typedef int Integer;
      void test2(bar<Integer *> *x);
    }
    Mangling is more consistent and changes from 
    _p_foo__barT_int_p_t to 
    _p_foo__barT_p_int_t.
*/
static void mangle_stringcopy(String *destination, const char *source, int count) {
  while (count-- > 0) {
    char newc = '_';
    if (!(*source == '.' || *source == ':' || *source == ' '))
      newc = *source;
    /* TODO: occasionally '*' or numerics need converting to '_', eg in array dimensions and template expressions */
    Putc(newc, destination);
    source++;
  }
}