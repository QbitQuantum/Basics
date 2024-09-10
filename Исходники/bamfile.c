static BAM_FILE _bamfile_open_r(SEXP filename, SEXP indexname, SEXP filemode)
{
    BAM_FILE bfile = (BAM_FILE) Calloc(1, _BAM_FILE);

    bfile->file = NULL;
    if (0 != Rf_length(filename)) {
        const char *cfile = translateChar(STRING_ELT(filename, 0));
        bfile->file = _bam_tryopen(cfile, CHAR(STRING_ELT(filemode, 0)), 0);
        if ((bfile->file->type & TYPE_BAM) != 1) {
            samclose(bfile->file);
            Free(bfile);
            Rf_error("'filename' is not a BAM file\n  file: %s", cfile);
        }
        bfile->pos0 = bam_tell(bfile->file->x.bam);
        bfile->irange0 = 0;
    }

    bfile->index = NULL;
    if (0 != Rf_length(indexname)) {
        const char *cindex = translateChar(STRING_ELT(indexname, 0));
        bfile->index = _bam_tryindexload(cindex);
        if (NULL == bfile->index) {
            samclose(bfile->file);
            Free(bfile);
            Rf_error("failed to open BAM index\n  index: %s\n", cindex);
        }
    }

    bfile->iter = NULL;
    bfile->pbuffer = NULL;
    return bfile;
}