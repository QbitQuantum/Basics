/*
** Die with a fatal error
*/
void xdie(char *msg) {
	fprintf(stderr, "FATAL: %s - exiting in %d seconds\n", msg, SEC_SLEEP);
	sleep(SEC_SLEEP); /* we get respawn by init - sleep */
	exit(1);
}