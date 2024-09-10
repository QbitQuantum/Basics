int read_brs_client(int row_start, int n_rows_to_get,
                    void *dest_void, void *read_client_info,
                    meta_parameters *meta, int data_type)
{
    // since we set "require_full_load", we should be reading in the
    // entire image
    assert(row_start == 0);
    assert(n_rows_to_get == meta->general->line_count);

    unsigned char *dest = (unsigned char*)dest_void;
    ReadBrsClientInfo *info = (ReadBrsClientInfo*)read_client_info;

    // these will explode if we ever call this fn a second time on
    // the same data.  Shouldn't happen, because we set "require_full_load"
    assert(info->fp);

    int ns = meta->general->sample_count;
    //unsigned char *brs_buf = MALLOC(ns * sizeof(unsigned char));
    int ii;

    // iterate over all rows in the brs
    for ( ii = 0; ii < n_rows_to_get; ii++ )
        FREAD(dest + ii*ns, sizeof(unsigned char), ns, info->fp);

    fclose(info->fp);
    info->fp = NULL;
    //FREE(brs_buf);

    return TRUE;
}