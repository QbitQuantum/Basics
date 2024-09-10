EFFECTGETARGS(frame,tags,PPTBase,EffectBase)
{
    struct convargs args = {0}, *saved;
    PERROR res;
    ULONG *rxargs;
    STRPTR buffer;

    SetDefaults(&args);

    if( saved = GetOptions(MYNAME) ) {
        args = *saved;
    }

    buffer = (STRPTR) TagData( PPTX_ArgBuffer, tags );

    rxargs = (ULONG *)TagData( PPTX_RexxArgs, tags );
    if(rxargs) {
        if( (res = LoadConvFilter( PPTBase, (UBYTE *)rxargs[0], &args )) != PERR_OK ) {
            SetErrorMsg(frame,"Couldn't open the specified convolution file");
            return PERR_FILEREAD;
        }
        strncpy( args.name, FilePart( (UBYTE *)rxargs[0] ), 40 );
    }

    if( (res = GetConvArgs( frame, tags, PPTBase, &args )) == PERR_OK ) {
        SaveConvFilter( PPTBase, TEMPFILENAME, &args );
        SPrintF( buffer, "FILE %s", TEMPFILENAME );
    }

    return res;
}