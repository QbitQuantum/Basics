static void syspgnumadfun( symvar *e ) // pagenumber.
{
    e = e;
    ultoa( page, syspgnumadstr, 10 );
    strcat( syspgnumadstr, "." );
    return;
};