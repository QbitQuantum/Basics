static int
gpsd_start(
	int     unit,
	peerT * peer)
{
	clockprocT * const pp = peer->procptr;
	gpsd_unitT * const up = emalloc_zero(sizeof(*up));

	struct stat sb;

	/* initialize the unit structure */
	up->fdt      = -1;
	up->addr     = s_gpsd_addr;
	up->tickpres = TICKOVER_LOW;

	/* setup refclock processing */
	up->unit    = unit;
	pp->unitptr = (caddr_t)up;
	pp->io.fd   = -1;
	pp->io.clock_recv = gpsd_receive;
	pp->io.srcclock   = peer;
	pp->io.datalen    = 0;
	pp->a_lastcode[0] = '\0';
	pp->lencode       = 0;
	pp->clockdesc     = DESCRIPTION;
	memcpy(&pp->refid, REFID, 4);

	/* Initialize miscellaneous variables */
	peer->precision = PRECISION;

	/* Create the device name and check for a Character Device. It's
	 * assumed that GPSD was started with the same link, so the
	 * names match. (If this is not practicable, we will have to
	 * read the symlink, if any, so we can get the true device
	 * file.)
	 */
	if (-1 == myasprintf(&up->device, "%s%u", s_dev_stem, unit)) {
	    msyslog(LOG_ERR, "%s clock device name too long",
		    refnumtoa(&peer->srcadr));
	    goto dev_fail;
	}
	if (-1 == stat(up->device, &sb) || !S_ISCHR(sb.st_mode)) {
		msyslog(LOG_ERR, "%s: '%s' is not a character device",
			refnumtoa(&peer->srcadr), up->device);
	    goto dev_fail;
	}
	LOGIF(CLOCKINFO,
	      (LOG_NOTICE, "%s: startup, device is '%s'",
	       refnumtoa(&peer->srcadr), up->device));
	return TRUE;

dev_fail:
	/* On failure, remove all UNIT ressources and declare defeat. */

	INSIST (up);
	free(up->device);
	free(up);

	pp->unitptr = (caddr_t)NULL;
	return FALSE;
}