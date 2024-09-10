char_t *websCalcNonce(webs_t wp)
{
	char_t		*nonce, *prenonce;
	time_t		longTime;
#if defined(WIN32)
	char_t		buf[26];
	errno_t	error;
	struct tm	newtime;
#else
	struct tm	*newtime;
#endif

	a_assert(wp);
/*
 *	Get time as long integer.
 */
	time(&longTime);
/*
 *	Convert to local time.
 */
#if !defined(WIN32)
	newtime = localtime(&longTime);
#else
	
	error = localtime_s(&newtime, &longTime);
#endif
/*
 *	Create prenonce string.
 */
#if !defined(WIN32)
	prenonce = NULL;
	fmtAlloc(&prenonce, 256, T("%s:%s:%s"), RANDOMKEY, gasctime(newtime),
		wp->realm); 
#else
	asctime_s(buf, elementsof(buf), &newtime);
	fmtAlloc(&prenonce, 256, T("%s:%s:%s"), RANDOMKEY, buf, 
		RANDOMKEY); 
#endif

	a_assert(prenonce);
/*
 *	Create the nonce
 */
    nonce = websMD5(prenonce);
/*
 *	Cleanup
 */
	bfreeSafe(B_L, prenonce);

	return nonce;
}