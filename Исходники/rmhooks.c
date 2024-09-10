void RemoveDOSIntercepts( void )    /* will undo the above */
{
    int i;

    for( i = 0; i < next_intr; ++i ) {
        _disable();
        INT_LOCATE( intr_list[i] ) = *old_intxx_handlers[i];
        _enable();
    }
    _disable();
    INT_LOCATE( 0x21 ) = old_int21;
    INT_LOCATE( 0x28 ) = old_int28;
    INT_LOCATE( 0x13 ) = old_int13;
    INT_LOCATE( 0x03 ) = old_int03;
    _enable();
}