int hdr_AddTextHeader( msg_Headers headers, const char * key,
        const char * value )
{
    msg_Header header = hdr_FindHeader( headers->text, key );

    if( !header )
    {
        header = Calloc( sizeof(struct _msg_Header), 1 );
        if( !header ) return 0;
        header->name = Strdup( key );
        if( !header->name )
        {
            Free( header );
            return 0;
        }
        header->values = slcreate();
        if( !header->values )
        {
            del_Header( header );
            return 0;
        }
        if( !sladd( header->values, value ) )
        {
            del_Header( header );
            return 0;
        }
    }

    return ladd( headers->text, header ) != NULL;
}