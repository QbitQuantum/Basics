static int
usal_sendreq(SCSI *usalp, struct usal_cmd *sp, struct dsreq *dsp)
{
	int	ret;
	int	retries = 4;
	Uchar	status;

/*	if ((sp->flags & SCG_CMD_RETRY) == 0)*/
/*		retries = 0;*/

	while (--retries > 0) {
		ret = ioctl(usalp->fd, DS_ENTER, dsp);
		if (ret < 0)  {
			RET(dsp) = DSRT_DEVSCSI;
			return (-1);
		}
		/*
		 * SGI implementattion botch!!!
		 * If a target does not select the bus,
		 * the return code is DSRT_TIMEOUT
		 */
		if (RET(dsp) == DSRT_TIMEOUT) {
			struct timeval to;

			to.tv_sec = TIME(dsp)/1000;
			to.tv_usec = TIME(dsp)%1000;
			__usal_times(usalp);

			if (sp->cdb.g0_cdb.cmd == SC_TEST_UNIT_READY &&
			    usalp->cmdstop->tv_sec < to.tv_sec ||
			    (usalp->cmdstop->tv_sec == to.tv_sec &&
				usalp->cmdstop->tv_usec < to.tv_usec)) {

				RET(dsp) = DSRT_NOSEL;
				return (-1);
			}
		}
		if (RET(dsp) == DSRT_NOSEL)
			continue;		/* retry noselect 3X */

		status = STATUS(dsp);
		switch (status) {

		case 0x08:		/*  BUSY */
		case 0x18:		/*  RESERV CONFLICT */
			if (retries > 0)
				sleep(2);
			continue;
		case 0x00:		/*  GOOD */
		case 0x02:		/*  CHECK CONDITION */
		case 0x10:		/*  INTERM/GOOD */
		default:
			return (status);
		}
	}
	return (-1);	/* failed retry limit */
}