int
le_put(struct iodesc *desc, void *pkt, size_t len)
{
#if 0
	struct netif *nif = desc->io_netif;
	int unit = nif->nif_unit;
#else
	int unit = 0;
#endif
	struct le_softc *sc = &le_softc[unit];
	volatile struct mds *cdm;
	int timo, i, stat;

 le_put_loop:
	timo = 100000;

#ifdef LE_DEBUG
	if (le_debug)
		printf("le%d: le_put called. next_td=%d\n", unit, sc->sc_next_td);
#endif
	stat = lerdcsr(sc, 0);
	lewrcsr(sc, 0, stat & (LE_BABL | LE_MISS | LE_MERR | LE_TINT));
	if (stat & (LE_BABL | LE_CERR | LE_MISS | LE_MERR))
		le_error(unit, "le_put(way before xmit)", stat);
	cdm = &sc->sc_td[sc->sc_next_td];
        i = 0;
#if 0
	while (cdm->flags & LE_OWN) {
		if ((i % 100) == 0)
			printf("le%d: output buffer busy - flags=%x\n",
				unit, cdm->flags);
		if (i++ > 500) break;
	}
	if (cdm->flags & LE_OWN)
		getchar();
#else
	while (cdm->flags & LE_OWN);
#endif
	bcopy(pkt, sc->sc_tbuf + (BUFSIZE * sc->sc_next_td), len);
	if (len < ETHER_MIN_LEN)
		cdm->bcnt = -ETHER_MIN_LEN;
	else
		cdm->bcnt = -len;
	cdm->mcnt = 0;
	cdm->flags |= LE_OWN | LE_STP | LE_ENP;
	stat = lerdcsr(sc, 0);
	if (stat & (LE_BABL | LE_CERR | LE_MISS | LE_MERR))
		le_error(unit, "le_put(before xmit)", stat);
	lewrcsr(sc, 0, LE_TDMD);
	stat = lerdcsr(sc, 0);
	if (stat & (LE_BABL | LE_CERR | LE_MISS | LE_MERR))
		le_error(unit, "le_put(after xmit)", stat);
	do {
		if (--timo == 0) {
			printf("le%d: transmit timeout, stat = 0x%x\n",
				unit, stat);
			if (stat & LE_SERR)
				le_error(unit, "le_put(timeout)", stat);
			if (stat & LE_INIT) {
				printf("le%d: reset and retry packet\n", unit);
				lewrcsr(sc, 0, LE_TINT);	/* sanity */
				le_init(desc, NULL);
				goto le_put_loop;
			}
			break;
		}
		stat = lerdcsr(sc, 0);
	} while ((stat & LE_TINT) == 0);
	lewrcsr(sc, 0, LE_TINT);
	if (stat & (LE_BABL |/* LE_CERR |*/ LE_MISS | LE_MERR)) {
		printf("le_put: xmit error, buf %d\n", sc->sc_next_td);
		le_error(unit, "le_put(xmit error)", stat);
	}
	if (++sc->sc_next_td >= NTBUF)
		sc->sc_next_td = 0;
	if (cdm->flags & LE_DEF)
		le_stats[unit].deferred++;
	if (cdm->flags & LE_ONE)
		le_stats[unit].collisions++;
	if (cdm->flags & LE_MORE)
		le_stats[unit].collisions+=2;
	if (cdm->flags & LE_ERR) {
		printf("le%d: transmit error, error = 0x%x\n", unit,
			cdm->mcnt);
		return -1;
	}
#ifdef LE_DEBUG
	if (le_debug) {
		printf("le%d: le_put() successful: sent %d\n", unit, len);
		printf("le%d: le_put(): flags: %x mcnt: %x\n", unit,
			(unsigned int) cdm->flags,
			(unsigned int) cdm->mcnt);
	}
#endif
	return len;
}