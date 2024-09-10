/******************************************************************
 ** Procedure:  PrettyTmpName (char * oldname)
 ** Procedure:  PrettyNewName (char * oldname)
 ** Parameters:  oldname
 ** Returns:  a new capitalized name
 ** Description:  creates a new name with first character's in caps
 ** Side Effects:  PrettyNewName allocates memory for the new name
 ** Status:   OK  7-Oct-1992 kcm
 ******************************************************************/
const char *
PrettyTmpName( const char * oldname ) {
    int i = 0;
    static char newname [BUFSIZ];
    newname [0] = '\0';
    while( ( oldname [i] != '\0' ) && ( i < BUFSIZ ) ) {
        newname [i] = ToLower( oldname [i] );
        if( oldname [i] == '_' ) { /*  character is '_'   */
            ++i;
            newname [i] = ToUpper( oldname [i] );
        }
        if( oldname [i] != '\0' ) {
            ++i;
        }
    }

    newname [0] = ToUpper( oldname [0] );
    newname [i] = '\0';
    return newname;
}