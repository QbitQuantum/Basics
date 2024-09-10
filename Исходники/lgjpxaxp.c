void longjmpex( jmp_buf jb, int ret )
{
    EXCEPTION_RECORD    er;
    _JUMPEXDATA         *jd = (_JUMPEXDATA *)jb;

    er.ExceptionCode           = 0xE5670123;
    er.ExceptionFlags          = 0x00000002;
    er.ExceptionRecord         = 0L;
    er.ExceptionAddress        = 0L;
    er.NumberParameters        = 1L;
    er.ExceptionInformation[0] = jd->sp;

    if( !_ProcSetsFP( RtlLookupFunctionEntry( jd->pc ) ) )
        RtlUnwind( (void *)jd->sp, (void *)jd->pc, &er, (void *)ret );
    else
        RtlUnwindRfp( jd->fp, jd->pc, &er, ret );
} /* longjmp() */