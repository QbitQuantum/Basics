static void
load_snap (SNAP *src, STRTAB *stab, SPWAW_SNAPSHOT *dst)
{
	int	i;

	dst->raw.game.cmt.title = STRTAB_getstr (stab, src->cmt.title);
	dst->raw.game.cmt.mapsrc = STRTAB_getstr (stab, src->cmt.mapsrc);

	getB (year); getB (month); getB (day); getB (hour);
	dst->raw.game.battle.location = STRTAB_getstr (stab, src->b.location);
	getB (terrain); getB (weather); getB (visibility); getB (turn); getB (turn_max);
	getB (OOB_p1); getB (OOB_p2); getB (OOB_p3); getB (OOB_p4);
	getB (miss_p1); getB (miss_p2); getB (credit);

	for (i=0; i<SNAP_VHEXCNT; i++) {
		dst->raw.game.battle.vhex[i].x = src->b.vhex[i].x;
		dst->raw.game.battle.vhex[i].y = src->b.vhex[i].y;
		dst->raw.game.battle.vhex[i].value = src->b.vhex[i].value;
		dst->raw.game.battle.vhex[i].owner = src->b.vhex[i].owner;
	}

	getC (campaign); getC (start_year); getC (start_month); getC (end_year); getC (end_month);
	getC (battles); getC (majvics); getC (minvics); getC (battles_max);
	getC (P1BLmen); getC (P1BLart); getC (P1BLsoft); getC (P1BLapc); getC (P1BLafv); getC (P1BLgliders); getC (P1BLair);
	getC (P2BLmen); getC (P2BLart); getC (P2BLsoft); getC (P2BLapc); getC (P2BLafv); getC (P2BLgliders); getC (P2BLair);
	getC (P1TLmen); getC (P1TLart); getC (P1TLsoft); getC (P1TLapc); getC (P1TLafv); getC (P1TLgliders); getC (P1TLair);
	getC (P2TLmen); getC (P2TLart); getC (P2TLsoft); getC (P2TLapc); getC (P2TLafv); getC (P2TLgliders); getC (P2TLair);
	getC (busy); getC (P1score); getC (P2score); getC (P1result); getC (P2result);
}