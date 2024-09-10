static SV *
get_op_bitspec(pTHX_ const char *opname, STRLEN len, int fatal)
{
    SV **svp;
    dMY_CXT;

    svp = hv_fetch(op_named_bits, opname, len, 0);
    if (!svp || !SvOK(*svp)) {
	if (!fatal)
	    return Nullsv;
	if (*opname == ':')
	    croak("Unknown operator tag \"%s\"", opname);
	if (*opname == '!')	/* XXX here later, or elsewhere? */
	    croak("Can't negate operators here (\"%s\")", opname);
	if (isALPHA(*opname))
	    croak("Unknown operator name \"%s\"", opname);
	croak("Unknown operator prefix \"%s\"", opname);
    }
    return *svp;
}