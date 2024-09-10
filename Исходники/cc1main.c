void GOL_sysabort(UCHAR termcode)
{
	GOL_abortcode = termcode;
	longjmp(setjmp_env, 1);
}