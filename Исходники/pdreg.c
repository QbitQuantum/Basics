_WCRTLINK void _NextExcInfo( _EXCINFO *info )
{
    info->ControlPC = RtlVirtualUnwind( info->ControlPC, info->FunctionEntry, &info->ContextRecord, &info->InFunction, info->EstablisherFrame, NULL );
    _SetPData( info );
}