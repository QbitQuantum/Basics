/**
 * Initialize authmodule
 *
 * @param l pointer to AuthMod
 * @param sb pointer to SystemBase
 * @return 0 when success, otherwise error number
 */
int libInit( AuthMod *l, void *sb )
{
	DEBUG("[FCDB] libinit\n");

	if( ( l->SpecialData = FCalloc( 1, sizeof( struct SpecialData ) ) ) == NULL )
	{
		FERROR("Cannot allocate memory for authmodule\n");
		return 1;
	}

	l->am_Name = LIB_NAME;
	l->am_Version = LIB_VERSION;
	l->sb = sb;

	return 0;
}