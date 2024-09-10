void import_gridfloat(char *inBaseName, char *outBaseName)
{
    int i, j;
    int column_count, row_count;
    char *flt_file = appendExt(inBaseName, ".flt");

    // create the metadata
    char *meta_filename = appendExt(outBaseName, ".meta");

    asfPrintStatus("Building %s ...\n", meta_filename);

    meta_parameters *meta = read_meta_gridfloat_ext(inBaseName, flt_file,
						    &column_count, &row_count);

    meta_write(meta, meta_filename);

    // Now read/write the actual data.  Read as INT16, cast to
    // floats so we can use put_float_line (which will write
    // INT16 data, since we asked for it in the metadata)
    char *data_filename = appendExt(outBaseName, ".img");

    asfPrintStatus("Reading %s, writing %s ...\n", flt_file, data_filename);

    float *floats = MALLOC(sizeof(float)*column_count);
    FILE *fp = FOPEN(flt_file, "rb");
    FILE *out = FOPEN(data_filename, "wb");

    for (i=0; i<row_count; ++i) {
        FREAD(floats, sizeof(float), column_count, fp);
	//if (msbfirst) {
            for (j=0; j<column_count; ++j) {
                big32(floats[j]);
            }
	    //}
        put_float_line(out, meta, i, floats);
        asfLineMeter(i,row_count);
    }

    fclose(fp);
    fclose(out);

    free(data_filename);
    free(floats);

    free(flt_file);
}