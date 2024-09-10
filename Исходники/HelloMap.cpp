//-------------------------------------------------------------------------
extern "C" int MAMain( )
//-------------------------------------------------------------------------
{
	HelloMap::HelloMapMoblet* moblet = newobject( HelloMap::HelloMapMoblet, new HelloMap::HelloMapMoblet( ) );

	Moblet::run( moblet );

	deleteobject( moblet );
	MapCache::shutdown( );

	MemoryMgr::dump( );
	return 0;
}