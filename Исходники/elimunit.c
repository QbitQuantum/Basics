static a_reduce_action *addReduceAction( a_pro *pro, a_word *follow, a_reduce_action *r )
{
    a_reduce_action *raction;
    a_reduce_action *new_raction;
    a_word *new_follow;
    size_t i;

    for( raction = r; raction->pro != NULL; ) {
        ++raction;
    }
    i = raction - r;
    new_follow = AllocSet( 1 );
    Assign( new_follow, follow );
    new_raction = REALLOC( r, i + 2, a_reduce_action );
    new_raction[i].pro = pro;
    new_raction[i].follow = new_follow;
    new_raction[i + 1].pro = NULL;
    new_raction[i + 1].follow = NULL;
    return( new_raction );
}