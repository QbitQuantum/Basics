void RewriteToken( void )
/***********************/
{
    REWRITE *r;
    REWRITE_TOKENS *rt;
    uint_8 *stop;
    uint_32 srcfile_index;
    SRCFILE srcfile;
    uint_32 absolute;
    int code_byte;
    unsigned len;

    r = currRewrite;
    rt = r->curr;
    stop = &(rt->stream[rt->count]);
    CurToken = getToken( r, &rt, &stop );
    if( CurToken == T_REWRITE_MODS ) {
        code_byte = getByte( r, &rt, &stop );
        if( code_byte == CODE_FILE ) {
            getBinary( r, &rt, &stop, (uint_8*)&srcfile_index, sizeof( srcfile_index ) );
            srcfile = accessSrcFile( r, srcfile_index );
            SrcFilePoint( srcfile );
            TokenLine = 0;
            TokenColumn = 0;
            CurToken = getToken( r, &rt, &stop );
            if( CurToken == T_REWRITE_MODS ) {
                code_byte = getByte( r, &rt, &stop );
            }
        }
    }
    if( CurToken == T_REWRITE_MODS ) {
        for( ;; ) {
            if( code_byte == CODE_ABS ) {
                getBinary( r, &rt, &stop, (uint_8*)&absolute, sizeof( absolute ) );
                if( MASK_ABS_LINE & absolute ) {
                    TokenLine = absolute & ~MASK_ABS_LINE;
                    TokenColumn = 0;
                } else {
                    TokenColumn = absolute;
                    break;
                }
            } else if( MASK_DELTA_LINE & code_byte ) {
                TokenLine += code_byte & ~MASK_DELTA_LINE;
            } else {
                TokenColumn += code_byte;
                break;
            }
            code_byte = getByte( r, &rt, &stop );
        }
        CurToken = getToken( r, &rt, &stop );
    }
    switch( CurToken ) {
    case T_ID:
    case T_BAD_CHAR:
        len = getString( r, &rt, &stop, Buffer );
        TokenLen = len;
        break;
    case T_BAD_TOKEN:
        getBinary( r, &rt, &stop, (uint_8*)&BadTokenInfo, sizeof( BadTokenInfo ) );
        break;
    case T_STRING:
    case T_LSTRING:
        len = getString( r, &rt, &stop, Buffer );
        TokenLen = len + 1;
        break;
    case T_CONSTANT:
        getBinary( r, &rt, &stop, (uint_8*)&ConstType, sizeof( ConstType ) );
        switch( ConstType ) {
        case TYP_LONG_DOUBLE:
        case TYP_DOUBLE:
        case TYP_FLOAT:
            len = getString( r, &rt, &stop, Buffer );
            TokenLen = len;
            break;
        default:
            getBinary( r, &rt, &stop, (uint_8*)&Constant64, sizeof( Constant64 ) );
            break;
        }
        break;
    default:
        break;
    }
#ifndef NDEBUG
    CtxScanToken();
    DumpToken();
#endif
}