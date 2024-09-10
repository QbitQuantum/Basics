static  macro_entry     *FindMacroEntry( char *macro, uint macro_len ) {
//======================================================================

// Find a macro.

    macro_entry *me;

    for( me = MacroList; me != NULL; me = me->link ) {
        if( me->name_len != macro_len ) continue;
        if( memicmp( me->name, macro, macro_len ) == 0 ) return( me );
    }
    return( NULL );
}