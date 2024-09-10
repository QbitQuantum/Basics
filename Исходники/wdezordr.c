bool WdeFindObjectsInRect( RECT *r, LIST **obj_list, LIST *olist )
{
    OBJPTR   child;
    RECT     child_rect;
    RECT     irect;

    *obj_list = NULL;

    for( ; olist != NULL; olist = ListNext( olist ) ) {
        child = ListElement( olist );
        Location( child, &child_rect );
        if( IntersectRect( &irect, &child_rect, r ) ) {
            WdeInsertObject( obj_list, child );
        }
    }

    return( *obj_list != NULL );
}