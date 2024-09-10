/**
 * Sets the WRITABLE attribute for the specified file or directory
 *
 * @param pathName      name in UNICODE of file or directory
 * @param pathNameLen   length of path name
 * @param value         JAVACALL_TRUE to set file as writable
 *                      JAVACALL_FALSE to set file as not writable
 * @return <tt>JAVACALL_OK</tt> if operation completed successfully
 *         <tt>JAVACALL_FAIL</tt> if an error occured
 */ 
javacall_result javacall_fileconnection_set_writable(const javacall_utf16* pathName,
                                                     int pathNameLen,
                                                     javacall_bool value) {

    wchar_t wOsFilename[JAVACALL_MAX_FILE_NAME_LENGTH]; // max file name

    if( pathNameLen > JAVACALL_MAX_FILE_NAME_LENGTH ) {
        javacall_print("Error: javacall_fileconnection_set_writable(), file name is too long\n");
        return JAVACALL_FAIL;
    }

    memcpy(wOsFilename, pathName, pathNameLen*sizeof(wchar_t));
    wOsFilename[pathNameLen] = 0;

    if(_wchmod(wOsFilename, (JAVACALL_TRUE == value) ? _S_IWRITE : _S_IREAD) == -1) {
        javacall_print("Error: javacall_fileconnection_set_writable(), file is not accessible\n");
        return JAVACALL_FAIL;
    }

    return JAVACALL_OK;
}