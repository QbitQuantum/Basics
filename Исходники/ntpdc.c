/*
 * abortcmd - catch interrupts and abort the current command
 */
static RETSIGTYPE
abortcmd(
	int sig
	)
{
	if (current_output == stdout)
		(void)fflush(stdout);
	putc('\n', stderr);
	(void)fflush(stderr);
	if (jump) {
		jump = 0;
		LONGJMP(interrupt_buf, 1);
	}
}