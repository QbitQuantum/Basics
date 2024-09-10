char *findparam( char *name )
{
	struct params *found, t;

	found = (struct params *)lfind( name, param, &paramcount, sizeof(struct params), paramcompar );
/*	found = (struct params *)qsearch( name, param, paramcount, sizeof(struct params), paramcompar ); */


	if ( found ) {
		memcpy( &t, found, sizeof(t) );
		memcpy( found, &(param[--paramcount]), sizeof(t) );
		memcpy( &(param[paramcount]), &t, sizeof(t) );
		return param[paramcount].value;
	} else return NULL;
}