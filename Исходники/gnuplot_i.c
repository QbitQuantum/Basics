void gnuplot_plot_xy(
    gnuplot_ctrl    *   handle,
	double			*	x,
	double			*	y,
    int                 n,
    char            *   title
)
{
    int         i ;
    FILE    *   tmp ;
    char    *   name ;
    char        cmd[GP_CMD_SIZE] ;
    char        line[GP_CMD_SIZE] ;

	if (handle==NULL || x==NULL || y==NULL || (n<1)) return ;

    /* can we open one more temporary file? */
    if (handle->ntmp == GP_MAX_TMP_FILES - 1) {
        fprintf(stderr,
                "maximum # of temporary files reached (%d): cannot open more",
                GP_MAX_TMP_FILES) ;
        return ;
    }

    /* Open temporary file for output   */
    if ((name = tmpnam(NULL)) == (char*)NULL) {
        fprintf(stderr,"cannot create temporary file: exiting plot") ;
        return ;
    }
    if ((tmp = fopen(name, "w")) == NULL) {
        fprintf(stderr,"cannot create temporary file: exiting plot") ;
        return ;
    }

    /* Store file name in array for future deletion */
    strcpy(handle->to_delete[handle->ntmp], name) ;
    handle->ntmp ++ ;

    /* Write data to this file  */
    for (i=0 ; i<n; i++) {
        fprintf(tmp, "%g %g\n", x[i], y[i]) ;
    }
    fflush(tmp) ;
    fclose(tmp) ;

    /* Command to be sent to gnuplot    */
    if (handle->nplots > 0) {
        strcpy(cmd, "replot") ;
    } else {
        strcpy(cmd, "plot") ;
    }
    
    if (title == NULL) {
        sprintf(line, "%s \"%s\" with %s", cmd, name, handle->pstyle) ;
    } else {
        sprintf(line, "%s \"%s\" title \"%s\" with %s", cmd, name,
                      title, handle->pstyle) ;
    }

    /* send command to gnuplot  */
    gnuplot_cmd(handle, line) ;
    handle->nplots++ ;
    return ;
}