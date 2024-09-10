static void
flags_set_sync_p2( sync_vars_t *svars, sync_rec_t *srec, int t )
{
	int nflags, nex;

	nflags = (srec->flags | srec->aflags[t]) & ~srec->dflags[t];
	if (srec->flags != nflags) {
		debug( "  pair(%d,%d): updating flags (%u -> %u)\n", srec->uid[M], srec->uid[S], srec->flags, nflags );
		srec->flags = nflags;
		Fprintf( svars->jfp, "* %d %d %u\n", srec->uid[M], srec->uid[S], nflags );
	}
	if (t == S) {
		nex = (srec->status / S_NEXPIRE) & 1;
		if (nex != ((srec->status / S_EXPIRED) & 1)) {
			if (nex && (svars->smaxxuid < srec->uid[S]))
				svars->smaxxuid = srec->uid[S];
			Fprintf( svars->jfp, "/ %d %d\n", srec->uid[M], srec->uid[S] );
			debug( "  pair(%d,%d): expired %d (commit)\n", srec->uid[M], srec->uid[S], nex );
			srec->status = (srec->status & ~S_EXPIRED) | (nex * S_EXPIRED);
		} else if (nex != ((srec->status / S_EXPIRE) & 1)) {
			Fprintf( svars->jfp, "\\ %d %d\n", srec->uid[M], srec->uid[S] );
			debug( "  pair(%d,%d): expire %d (cancel)\n", srec->uid[M], srec->uid[S], nex );
			srec->status = (srec->status & ~S_EXPIRE) | (nex * S_EXPIRE);
		}
	}
}