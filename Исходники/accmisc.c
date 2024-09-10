BOOL IsBigSel( WORD sel )
{
#if defined( MD_axp ) | defined( MD_ppc )
    return( TRUE );
#elif defined( MD_x86 ) || defined( MD_x64 )
    thread_info *ti;
    LDT_ENTRY   ldt;

    if( sel == FlatCS || sel == FlatDS ) {
        return( TRUE );
    }
    ti = FindThread( DebugeeTid );
    if( ti == NULL ) {
        return( TRUE );
    }
    GetThreadSelectorEntry( ti->thread_handle, sel, &ldt );
    return( ldt.HighWord.Bits.Default_Big );
#else
   #error IsBigSel not configured
#endif
}