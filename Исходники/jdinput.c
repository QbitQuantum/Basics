initial_setup (j_decompress_ptr cinfo)
/* Called once, when first SOS marker is reached */
{
    int ci;
    jpeg_component_info *compptr;

    /* Make sure image isn't bigger than I can handle */
    if ((long) cinfo->image_height > (long) JPEG_MAX_DIMENSION ||
            (long) cinfo->image_width > (long) JPEG_MAX_DIMENSION)
        ERREXIT1(cinfo, JERR_IMAGE_TOO_BIG, (unsigned int) JPEG_MAX_DIMENSION);

    if (cinfo->process == JPROC_LOSSLESS) {
        /* If precision > compiled-in value, we must downscale */
        if (cinfo->data_precision > BITS_IN_JSAMPLE)
            WARNMS2(cinfo, JWRN_MUST_DOWNSCALE,
                    cinfo->data_precision, BITS_IN_JSAMPLE);
    }
    else {  /* Lossy processes */
        /* For now, precision must match compiled-in value... */
        if (cinfo->data_precision != BITS_IN_JSAMPLE)
            ERREXIT1(cinfo, JERR_BAD_PRECISION, cinfo->data_precision);
    }

    /* Check that number of components won't exceed internal array sizes */
    if (cinfo->num_components > MAX_COMPONENTS)
        ERREXIT2(cinfo, JERR_COMPONENT_COUNT, cinfo->num_components,
                 MAX_COMPONENTS);

    /* Compute maximum sampling factors; check factor validity */
    cinfo->max_h_samp_factor = 1;
    cinfo->max_v_samp_factor = 1;
    for (ci = 0, compptr = cinfo->comp_info; ci < cinfo->num_components;
            ci++, compptr++) {
        if (compptr->h_samp_factor<=0 || compptr->h_samp_factor>MAX_SAMP_FACTOR ||
                compptr->v_samp_factor<=0 || compptr->v_samp_factor>MAX_SAMP_FACTOR)
            ERREXIT(cinfo, JERR_BAD_SAMPLING);
        cinfo->max_h_samp_factor = MAX(cinfo->max_h_samp_factor,
                                       compptr->h_samp_factor);
        cinfo->max_v_samp_factor = MAX(cinfo->max_v_samp_factor,
                                       compptr->v_samp_factor);
    }

    /* We initialize codec_data_unit and min_codec_data_unit to data_unit.
     * In the full decompressor, this will be overridden by jdmaster.c;
     * but in the transcoder, jdmaster.c is not used, so we must do it here.
     */
    cinfo->min_codec_data_unit = cinfo->data_unit;

    /* Compute dimensions of components */
    for (ci = 0, compptr = cinfo->comp_info; ci < cinfo->num_components;
            ci++, compptr++) {
        compptr->codec_data_unit = cinfo->data_unit;
        /* Size in data units */
        compptr->width_in_data_units = (JDIMENSION)
                                       jdiv_round_up((long) cinfo->image_width * (long) compptr->h_samp_factor,
                                               (long) (cinfo->max_h_samp_factor * cinfo->data_unit));
        compptr->height_in_data_units = (JDIMENSION)
                                        jdiv_round_up((long) cinfo->image_height * (long) compptr->v_samp_factor,
                                                (long) (cinfo->max_v_samp_factor * cinfo->data_unit));
        /* downsampled_width and downsampled_height will also be overridden by
         * jdmaster.c if we are doing full decompression.  The transcoder library
         * doesn't use these values, but the calling application might.
         */
        /* Size in samples */
        compptr->downsampled_width = (JDIMENSION)
                                     jdiv_round_up((long) cinfo->image_width * (long) compptr->h_samp_factor,
                                             (long) cinfo->max_h_samp_factor);
        compptr->downsampled_height = (JDIMENSION)
                                      jdiv_round_up((long) cinfo->image_height * (long) compptr->v_samp_factor,
                                              (long) cinfo->max_v_samp_factor);
        /* Mark component needed, until color conversion says otherwise */
        compptr->component_needed = TRUE;
        /* Mark no quantization table yet saved for component */
        compptr->quant_table = NULL;
    }

    /* Compute number of fully interleaved MCU rows. */
    cinfo->total_iMCU_rows = (JDIMENSION)
                             jdiv_round_up((long) cinfo->image_height,
                                           (long) (cinfo->max_v_samp_factor*cinfo->data_unit));

    /* Decide whether file contains multiple scans */
    if (cinfo->comps_in_scan < cinfo->num_components ||
            cinfo->process == JPROC_PROGRESSIVE)
        cinfo->inputctl->has_multiple_scans = TRUE;
    else
        cinfo->inputctl->has_multiple_scans = FALSE;
}