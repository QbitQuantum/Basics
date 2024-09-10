int
dem_to_mask(char *inDemFile, char *outMaskFile, float cutoff)
{
    meta_parameters *inDemMeta = meta_read(inDemFile);
    meta_parameters *outDemMeta = meta_read(inDemFile);

    // out metadata will differ from in only in the data type
    outDemMeta->general->data_type = ASF_BYTE;

    int x_size = inDemMeta->general->sample_count;
    int y_size = inDemMeta->general->line_count;

    float *maskbuffer = MALLOC(sizeof(float) * x_size);
    float *floatbuffer = MALLOC(sizeof(float) * x_size);

    FILE *in = fopenImage(inDemFile, "rb");
    FILE *out = fopenImage(outMaskFile, "wb");

    float mv = masked_value();
    float umv = unmasked_value();

    int y,x;
    for (y=0; y<y_size; y++) 
    {
        get_float_line(in, inDemMeta, y, floatbuffer);

        for (x=0; x < x_size; x++)            
            maskbuffer[x] = floatbuffer[x] <= cutoff ? mv : umv;

        put_float_line(out, outDemMeta, y, maskbuffer);
        asfLineMeter(y, y_size);
    }

    FCLOSE(in);
    FCLOSE(out);

    FREE(floatbuffer);
    FREE(maskbuffer);

    meta_write(outDemMeta, outMaskFile);

    meta_free(inDemMeta);
    meta_free(outDemMeta);

    asfPrintStatus("Created Mask file '%s' from DEM '%s'.\n",
                   outMaskFile, inDemFile);

    return 0;
}