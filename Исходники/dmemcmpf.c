int _fMemiCmp(const byte far * dest, const byte far * src, unsigned length)
{	int d;

	DBG_ENTER("_fMemiCmp", Suppl_farmem)

	if(!length)
		DBG_RETURN_I( 0)

	if(dest == 0)
		DBG_RETURN_I(src != 0)
	if(src == 0)
		DBG_RETURN_I(-1)

	while((d = toUpper(*dest++) - toUpper(*src++)) == 0 && --length);

	DBG_RETURN_I( d)
}