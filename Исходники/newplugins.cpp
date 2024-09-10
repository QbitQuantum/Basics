// perform any API related tasks to freeing
static void Plugin_Uninit(pluginEntry * p)
{
	// if it was an installed database plugin, call its unload
	if ( p->pclass & PCLASS_DB )
		p->bpi.dblink->Unload( p->pclass & PCLASS_OK );

	// if the basic API check had passed, call Unload if Load() was ever called
	if ( p->pclass & PCLASS_LOADED )
		p->bpi.Unload();

	// release the library
	if ( p->bpi.hInst != NULL ) {
		// we need to kill all resources which belong to that DLL before calling FreeLibrary
		KillModuleEventHooks( p->bpi.hInst );
		KillModuleServices( p->bpi.hInst );

		FreeLibrary( p->bpi.hInst );
		ZeroMemory( &p->bpi, sizeof( p->bpi ));
	}
	pluginList.remove( p );
	pluginListAddr.remove( p );
}