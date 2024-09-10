static RIFFIOSuccess
cbLogicalPlacement(NIFFIOTagContext *pctxTag, niffLogicalPlacement *p)
{
	extern void debugMeAt(mpq_t t);
	debugMeAt(t_current);

    if (cbTagStart(pctxTag, p, cbLogicalPlacement)) {
        assert(pctxTag != 0);
        assert(pctxTag->pnf != 0);
        assert(pctxTag->pchunkParent != 0);

        if (symbol_current != NULL && symbol_current->type == SYM_STEM &&
            p->vertical != 0) {
            symbol_current->symbol.stem.flags |= FLAG_STEM_EXPLICIT;
            if (p->vertical == 1) {
                symbol_current->symbol.stem.flags |= FLAG_STEM_UP;
            }
        } else {
            VPRINTF(" = (%d,%d) (proximity %d)", p->horizontal, p->vertical, p->proximity);
        }
    }
    cbTagEnd(pctxTag);

    return RIFFIO_OK;
}