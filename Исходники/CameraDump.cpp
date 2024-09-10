int CameraDump::dumpImage2File(camera_delay_dumpImage_T *aDumpImage, const char *name)
{
    LOG1("@%s", __FUNCTION__);
    void *data = aDumpImage->buffer_raw;
    unsigned int size = aDumpImage->buffer_size;
    unsigned int width = aDumpImage->width;
    unsigned int height = aDumpImage->height;
    unsigned int bpl = aDumpImage->bpl;
    char filename[80];
    static unsigned int count = 0;
    size_t bytes;
    FILE *fp;
    ia_binary_data *uMknData = NULL;
    char rawdpp[100];
    int ret;

    if ((NULL == data) || (0 == size) || (0 == width) || (0 == height) || (NULL == name)
            || (NULL == m3AControls))
        return -ERR_D2F_EVALUE;

    LOG2("%s filename is %s", __func__, name);
    /* media server may not have the access to SD card */
    showMediaServerGroup();

    ret = getRawDataPath(rawdpp);
    LOG2("RawDataPath is %s", rawdpp);
    if(-ERR_D2F_NOPATH == ret) {
        ALOGE("%s No valid mem for rawdata", __func__);
        return ret;
    }
    if ((strcmp(name, "raw.bayer") == 0) && (m3AControls != NULL))
    {
        /* Only RAW image will have same file name as JPEG */
        char filesuffix[20];
        time_t rawtime;
        struct tm *timeinfo;
        time(&rawtime);
        timeinfo = localtime(&rawtime);

        if (timeinfo) {
            strftime((char *)filename, sizeof(filename) - sizeof(filesuffix), "IMG_%Y%m%d_%H%M%S", timeinfo);
        } else {
            snprintf((char *)filename, sizeof(filename) - sizeof(filesuffix), "IMG_%s", "notime");
        }

        snprintf(filesuffix, sizeof(filesuffix), "%03u.i3av4", count);
        strncat(filename, filesuffix, sizeof(filename) - strlen(filename) - 1);
        strncat(rawdpp, filename, strlen(filename));

        ia_aiq_raw_image_full_info raw_info;
        raw_info.raw_image.data_format = ia_aiq_data_format_rawplain16;
        raw_info.raw_image.bayer_order = ia_aiq_bayer_order_grbg;
        raw_info.raw_image.data_format_bpp = 16;
        raw_info.raw_image.data_bpp = 10;
        raw_info.raw_image.width_cols = bytesToPixels(V4L2_PIX_FMT_SBGGR10, bpl);
        raw_info.raw_image.height_lines = height;
        raw_info.header_size_bytes = 0;
        raw_info.footer_size_bytes = 0;
        raw_info.extra_bytes_left = 0;
        raw_info.extra_bytes_right = 0;
        raw_info.extra_lines_top = 0;
        raw_info.extra_cols_left = 0;
        raw_info.extra_cols_right = 0;
        raw_info.extra_lines_bottom = 0;
        raw_info.byte_order_xor = 0;
        raw_info.spatial_sampling = 0;

        // Add raw image info to the maker note.
        m3AControls->add3aMakerNoteRecord(ia_mkn_dfid_unsigned_char, ia_mkn_dnid_hal_records, &raw_info, sizeof(ia_aiq_raw_image_full_info));

        // Get detailed maker note data
        uMknData = m3AControls->get3aMakerNote(ia_mkn_trg_section_2);
        if (uMknData) {
            ALOGD("RAW, mknSize: %d", uMknData->size);
        } else {
            ALOGW("RAW, no makernote");
        }
    }
    else
    {
        snprintf(filename, sizeof(filename), "dump_%d_%d_%03u_%s", width,
                 height, count, name);
        strncat(rawdpp, filename, strlen(filename));
    }

    fp = fopen (rawdpp, "w+");
    if (fp == NULL) {
        ALOGE("open file %s failed %s", rawdpp, strerror(errno));
        if (uMknData) {
            // Delete Maker note data
            m3AControls->put3aMakerNote(uMknData);
        }
        return -ERR_D2F_EOPEN;
    }

    LOG1("Begin write image %s", filename);

    if (uMknData && uMknData->size > 0)
    {
        if ((bytes = fwrite(uMknData->data, uMknData->size, 1, fp)) < (size_t)uMknData->size)
            ALOGW("Write less mkn bytes to %s: %d, %d", filename, uMknData->size, bytes);
    }

    if ((bytes = fwrite(data, size, 1, fp)) < (size_t)size)
        ALOGW("Write less raw bytes to %s: %d, %d", filename, size, bytes);

    count++;

    if (uMknData)
    {
        // Delete Maker note data
        m3AControls->put3aMakerNote(uMknData);
    }

    fclose (fp);

    return ERR_D2F_SUCESS;
}