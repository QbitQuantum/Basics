static walk_result CheckFirstFile( cue_handle *ch, void *_d )
{
    cue_mod     *d = _d;
    char        *buff;
    unsigned    len;

    len = CueFile( ch, NULL, 0 ) + 1;
    _AllocA( buff, len );
    CueFile( ch, buff, len );
    if( stricmp( buff, d->file ) == 0 ) {
        d->found = true;
    }
    return( WR_STOP );
}