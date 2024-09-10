latan_errno plot_save(const strbuf dirname, plot *p)
{
    strbuf path,buf,*datfname_bak,term_bak,output_bak;
    FILE *outf;
    size_t i,j,lc;
    mode_t mode_755;
    strbuf name,ver,err_msg;
    
    MALLOC_ERRVAL(datfname_bak,strbuf *,p->nplot,LATAN_ENOMEM);
    
    mode_755 = S_IRWXU|S_IRGRP|S_IXGRP|S_IROTH|S_IXOTH;
    
    /* backup I/O parameters */
    strbufcpy(term_bak,p->term);
    strbufcpy(output_bak,p->output);
    for (i=0;i<p->nplot;i++)
    {
        strbufcpy(datfname_bak[i],p->datfname[i]);
    }
    /* generate directory */
    if (access(dirname,R_OK|W_OK|X_OK))
    {
        if (mkdir(dirname,mode_755))
        {
            sprintf(err_msg,"impossible to create directory %s",dirname);
            LATAN_ERROR(err_msg,LATAN_ESYSTEM);
        }
    }
    /* save pdf */
    sprintf(path,"%s/plot.pdf",dirname);
    plot_set_term(p,"pdf");
    plot_set_output(p,path);
    plot_disp(p);
    plot_set_term(p,term_bak);
    plot_set_output(p,output_bak);
    /* save script and datafiles */
    j = 0;
    for (i=0;i<p->nplot;i++)
    {
        if (strlen(p->datfname[i]))
        {
            sprintf(p->datfname[i],"points_%lu.dat",(long unsigned)(j));
            j++;
            sprintf(path,"%s/%s",dirname,p->datfname[i]);
            FOPEN(outf,path,"w");
            BEGIN_FOR_LINE(buf,datfname_bak[i],lc)
            {
                fprintf(outf,"%s\n",buf);
            }
            END_FOR_LINE
            fclose(outf);
        }