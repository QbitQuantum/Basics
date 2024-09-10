void
dartstart(struct tty *tp)
{
	struct dartsoftc *sc;
	dev_t dev;
	int s;
	int port, tries;
	int c;
	bus_addr_t ptaddr;

	dev = tp->t_dev;
	port = DART_PORT(dev);
	if (dart_cd.cd_ndevs == 0 || port >= NDARTPORTS)
		return;

	if ((tp->t_state & TS_ISOPEN) == 0)
		return;

	sc = (struct dartsoftc *)dart_cd.cd_devs[0];
	ptaddr = port ? DART_B_BASE : DART_A_BASE;

	s = spltty();

	if (tp->t_state & (TS_TIMEOUT | TS_BUSY | TS_TTSTOP))
		goto bail;

	if (tp->t_outq.c_cc <= tp->t_lowat) {
		if (tp->t_state & TS_ASLEEP) {
			tp->t_state &= ~TS_ASLEEP;
			wakeup((caddr_t)&tp->t_outq);
		}
		selwakeup(&tp->t_wsel);
		if (tp->t_outq.c_cc == 0)
			goto bail;
	}

	tp->t_state |= TS_BUSY;
	while (tp->t_outq.c_cc != 0) {

		/* load transmitter until it is full */
		for (tries = 10000; tries != 0; tries --)
			if (dart_read(sc, ptaddr + DART_SRA) & TXRDY)
				break;

		if (tries == 0) {
			timeout_add(&tp->t_rstrt_to, 1);
			tp->t_state |= TS_TIMEOUT;
			break;
		} else {
			c = getc(&tp->t_outq);

			dart_write(sc, ptaddr + DART_TBA, c & 0xff);

			if (port == A_PORT)
				sc->sc_sv_reg.sv_imr |= ITXRDYA;
			else
				sc->sc_sv_reg.sv_imr |= ITXRDYB;
			dart_write(sc, DART_IMR, sc->sc_sv_reg.sv_imr);
		}
	}
	tp->t_state &= ~TS_BUSY;

bail:
	splx(s);
}