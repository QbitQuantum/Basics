static void nextExcInfo         // MOVE AHEAD TO NEXT RTN. IN CALL CHAIN
    ( __EXC_INFO* info )        // - exception info
{
    info->dctx.pc = RtlVirtualUnwind( info->dctx.pc
                                    , info->dctx.pdata
                                    , &info->ctx
                                    , &info->in_func
                                    , info->est_frame
                                    , 0 );
    setPdata( info );
}