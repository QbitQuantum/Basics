static uintptr_t CPROC SetDownIntro( uintptr_t psv, arg_list args )
{
	PARAM( args, int64_t, down );
	PARAM( args, CTEXTSTR, data );
	ffl.downs[down-1] = StrDup( data );
	return psv;
}