void aafCreateGUID( GUID *p_guid )
{
#if defined( OS_WINDOWS )

    assert( p_guid );
    CoCreateGuid( p_guid );

#else

    // {1994bd00-69de-11d2-b6bc-fcab70ff7331}
    static GUID	sTemplate = { 0x1994bd00,  0x69de,  0x11d2,
			{ 0xb6, 0xbc, 0xfc, 0xab, 0x70, 0xff, 0x73, 0x31 } };
    static int	sInitializedTemplate = 0;


    assert( p_guid );

    if( !sInitializedTemplate )
    {
	aafUInt32	ticks = aafGetTickCount();

	time_t		timer = time( NULL );
	sTemplate.Data1 += timer + ticks;
	sInitializedTemplate = 1;
    }

    // Just bump the first member of the guid to emulate GUIDGEN behavior.
    ++sTemplate.Data1;
    *p_guid = sTemplate;

#endif    // OS_*
}