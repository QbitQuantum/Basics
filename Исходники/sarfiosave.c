/*
 *	Saves the list of parameters to file.
 *
 *      The given file_format is a hint to the file's format.
 *
 *      Returns non-zero on error.
 */
int SARParmSaveToFile(
        const char *filename, int file_format,
        void **parm, int total_parms,
        void *client_data,
        int (*progress_func)(void *, long, long)
)
{
        int status = -1;
        FILE *fp;


        if(filename == NULL)
            return(status);

        /* Open file for writing. */
        fp = FOpen(filename, "wb");
        if(fp == NULL)
            return(status);

        /* Save by file format type. */
	if(1)
        {
            status = SARParmSaveToFileAny(
                filename, fp,
                parm, total_parms,
                client_data, progress_func
            );
        }

        /* Close file. */
        FClose(fp);

        return(status);
}