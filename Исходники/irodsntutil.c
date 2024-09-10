int iRODSNt_stat(const char *filename,struct irodsntstat *stat_p)
{
        char ntfp[2048];
        iRODSPathToNtPath(ntfp,filename);
        return _stat64(ntfp,stat_p);    /* _stat */
}