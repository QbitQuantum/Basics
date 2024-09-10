/* Taking the address of a builtin with a library "fallback" must be
   allowed, either using the __builtin_xxx form or the xxx form, when
   the library fallback is declared either explicitly or implicitly
   by virtue of first calling the function.  */
void test_taking_address_of_library_builtin (int i)
{
  {
    typedef int F (int);

    /* Compute the address of libc's abs using the implicitly declared
       __builtin_abs form (all expressions are valid).  */
    F *p = __builtin_abs;
    p = &__builtin_abs;
    p = *__builtin_abs;

    /* Compute the address of libc's abs declared above.  */
    p = abs;
    p = &abs;
    p = *abs;
    (void)p;
  }

  {
    typedef __SIZE_TYPE__ size_t;
    typedef size_t F (const char*);

    /* Compute the address of libc's strlen using the implicitly
       declared __builtin_strlen form.  */
    F *p = __builtin_strlen;
    p = &__builtin_strlen;
    p = *__builtin_strlen;

    /* Compute the address of libc's strlen declared above.  */
    p = strlen;
    p = &strlen;
    p = *strlen;
    (void)p;
  }

  {
    typedef int F (int);

    /* Compute the address of libc's isxxx functions using the implicitly
       declared __builtin_xxx form.  */
    F *p = __builtin_isalnum;
    p = &__builtin_isalpha;
    p = *__builtin_iscntrl;

    /* According to C90 (see also the discussion in c/67386):
       If the expression that precedes the parenthesized argument list
       in a function call consists solely of an identifier, and if no
       declaration is visible for this identifier, the identifier is
       implicitly declared exactly as if, in the innermost block
       containing the function call, the declaration
       extern int identifier();
       appeared.  */

    /* Call the functions first to have their declarations "injected"
       into the enclosing block.  Suppress warnings.  */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wimplicit-function-declaration"
    i = isalnum (i) || isalpha (i) || iscntrl (i);
#pragma GCC diagnostic pop

    /* Take the address of the functions relying on their declarations
       having been implicitly provided by the calls above.  */
    p = isalnum;
    p = &isalpha;
    p = *iscntrl;
    (void)p;
  }
}