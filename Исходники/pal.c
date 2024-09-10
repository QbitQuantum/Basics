/* File communication with the "Target" */
QSpyStatus PAL_openTargetFile(char const *fName) {
    /* setup the PAL virtual table for the File connection... */
    PAL_vtbl.getEvt      = &file_getEvt;
    PAL_vtbl.send2Target = &file_send2Target;
    PAL_vtbl.cleanup     = &file_cleanup;

    FOPEN_S(l_file, fName, "rb"); /* open for reading binary */
    if (l_file != (FILE *)0) {
        printf("\nFile %s opened, hit any key to quit...\n\n", fName);
        return QSPY_SUCCESS;
    }
    else {
        fprintf(stderr, "*** PAL: file %s not found\n", fName);
        return QSPY_ERROR;
    }
}