vx_status vxFReadImage(vx_array file, vx_image output)
{
    vx_char *filename = NULL;
    vx_size filename_stride = 0;
    vx_uint8 *src = NULL;
    vx_uint32 p = 0u, y = 0u;
    vx_size planes = 0u;
    vx_imagepatch_addressing_t addr = {0};
    vx_df_image format = VX_DF_IMAGE_VIRT;
    FILE *fp = NULL;
    vx_char tmp[VX_MAX_FILE_NAME] = {0};
    vx_char *ext = NULL;
    vx_rectangle_t rect;
    vx_uint32 width = 0, height = 0;

    vx_status status = vxAccessArrayRange(file, 0, VX_MAX_FILE_NAME, &filename_stride, (void **)&filename, VX_READ_ONLY);
    if (status != VX_SUCCESS || filename_stride != sizeof(vx_char))
    {
        vxAddLogEntry((vx_reference)file, VX_FAILURE, "Incorrect array "VX_FMT_REF"\n", file);
        return VX_FAILURE;
    }
    fp = fopen(filename, "rb");
    if (fp == NULL) {
        vxAddLogEntry((vx_reference)file, VX_FAILURE, "Failed to open file %s\n",filename);
        return VX_FAILURE;
    }

    vxQueryImage(output, VX_IMAGE_PLANES, &planes, sizeof(planes));
    vxQueryImage(output, VX_IMAGE_FORMAT, &format, sizeof(format));

    ext = strrchr(filename, '.');
    if (ext && (strcmp(ext, ".pgm") == 0 || strcmp(ext, ".PGM") == 0))
    {
        FGETS(tmp, fp); // PX
        FGETS(tmp, fp); // comment
        FGETS(tmp, fp); // W H
        sscanf(tmp, "%u %u", &width, &height);
        FGETS(tmp, fp); // BPP
        // ! \todo double check image size?
    }
    else if (ext && (strcmp(ext, ".yuv") == 0 ||
                     strcmp(ext, ".rgb") == 0 ||
                     strcmp(ext, ".bw") == 0))
    {
        sscanf(filename, "%*[^_]_%ux%u_%*s", &width, &height);
    }

    rect.start_x = rect.start_y = 0;
    rect.end_x = width;
    rect.end_y = height;

    for (p = 0; p < planes; p++)
    {
        status = vxAccessImagePatch(output, &rect, p, &addr, (void **)&src, VX_WRITE_ONLY);
        if (status == VX_SUCCESS)
        {
            for (y = 0; y < addr.dim_y; y+=addr.step_y)
            {
                vx_uint8 *srcp = vxFormatImagePatchAddress2d(src, 0, y, &addr);
                vx_size len = ((addr.dim_x * addr.scale_x)/VX_SCALE_UNITY);
                vx_size rlen = fread(srcp, addr.stride_x, len, fp);
                if (rlen != len)
                {
                    status = VX_FAILURE;
                    break;
                }
            }
            if (status == VX_SUCCESS)
            {
                status = vxCommitImagePatch(output, &rect, p, &addr, src);
            }
            if (status != VX_SUCCESS)
            {
                break;
            }
        }
        /* src pointer should be made NULL , otherwise the first plane data gets over written. */
        src = NULL;
    }
    fclose(fp);
    vxCommitArrayRange(file, 0, 0, filename);

    return status;
}