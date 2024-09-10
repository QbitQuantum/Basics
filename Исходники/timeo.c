void updateTimeout(Timeout *timeout, const long double sampleRTT) {
	//char LOG[300];
	if (pthread_rwlock_wrlock(&(timeout->rwlock)) > 0)
		ERREXIT("Cannot acquire timeout write-lock for updating value.");

	timeout->extRTT = RUDP_EXTRTT_A * timeout->extRTT + RUDP_EXTRTT_B * sampleRTT;

	timeout->devRTT = RUDP_DEVRTT_A * timeout->devRTT + RUDP_DEVRTT_B * fabsl(timeout->extRTT - sampleRTT);

	timeout->value = RUDP_TIMEO_A * timeout->extRTT + RUDP_TIMEO_B * timeout->devRTT;
	/*
	sprintf(LOG, "%LF\t%LF\t%LF\n", timeout->extRTT, timeout->devRTT, timeout->value);

	errno = 0;
	if (write(LOGFILE, LOG, strlen(LOG)) == -1)
		ERREXIT("Cannot write timeout log file: %s.", strerror(errno));
	*/

	if (pthread_rwlock_unlock(&(timeout->rwlock)) > 0)
		ERREXIT("Cannot release timeout read-write lock for updating value.");
}