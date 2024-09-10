/* fphandler handles SIGFPE (floating-point error) interrupt. Note
 * that this prototype accepts two arguments and that the 
 * prototype for signal in the run-time library expects a signal 
 * handler to have only one argument.
 *
 * The second argument in this signal handler allows processing of
 * _FPE_INVALID, _FPE_OVERFLOW, _FPE_UNDERFLOW, and 
 * _FPE_ZERODIVIDE, all of which are Microsoft-specific symbols 
 * that augment the information provided by SIGFPE. The compiler 
 * will generate a warning, which is harmless and expected.

 */
void fphandler(int sig, int num)
{
    /* Set global for outside check since we don't want
     * to do I/O in the handler.
    */
    fperr = num;
    /* Initialize floating-point package. */
    _fpreset();
    /* Restore calling environment and jump back to setjmp. Return 
    * -1 so that setjmp will return false for conditional test.
    */
    printf("about to do longjmp\n");
    fflush(stdout);
    longjmp(mark, -1);
}