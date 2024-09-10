void dispose_ban( BAN_DATA * pban, int type )
{
    if( !pban )
        return;

    if( type != BAN_SITE && type != BAN_CLASS && type != BAN_RACE )
    {
        bug( "%s: Unknown Ban Type %d.", __func__, type );
        return;
    }

    switch ( type )
    {
    case BAN_SITE:
        UNLINK( pban, first_ban, last_ban, next, prev );
        break;
    case BAN_CLASS:
        UNLINK( pban, first_ban_class, last_ban_class, next, prev );
        break;
    case BAN_RACE:
        UNLINK( pban, first_ban_race, last_ban_race, next, prev );
        break;
    }
    free_ban( pban );
}