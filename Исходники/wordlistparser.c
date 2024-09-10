bool Wordlist_selectionsEqual( unichar_t* s1, unichar_t* s2 )
{
    static unichar_t s1stripped[ PATH_MAX ];
    static unichar_t s2stripped[ PATH_MAX ];
    int s1HasSelection = 0;
    int s2HasSelection = 0;

    u_strcpy( s1stripped, Wordlist_selectionStringOnly( s1, &s1HasSelection ));
    u_strcpy( s2stripped, Wordlist_selectionStringOnly( s2, &s2HasSelection ));

    if( s1HasSelection && !s2HasSelection )
	return false;
    if( !s1HasSelection && s2HasSelection )
	return false;

    return !u_strcmp( s1stripped, s2stripped );
}