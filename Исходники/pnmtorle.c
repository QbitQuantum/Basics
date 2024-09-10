/*-----------------------------------------------------------------------------
 *                                        Read the pnm image file header.
 */
static void
read_pnm_header()
{
    pnm_readpnminit(fp, &width, &height, &maxval, &format);
    switch (format) {
    case PBM_FORMAT:
        VPRINTF(stderr, "Image type: plain pbm format\n");
        break;
    case RPBM_FORMAT:
        VPRINTF(stderr, "Image type: raw pbm format\n");
        break;
    case PGM_FORMAT:
        VPRINTF(stderr, "Image type: plain pgm format\n");
        break;
    case RPGM_FORMAT:
        VPRINTF(stderr, "Image type: raw pgm format\n");
        break;
    case PPM_FORMAT:
        VPRINTF(stderr, "Image type: plain ppm format\n");
        break;
    case RPPM_FORMAT:
        VPRINTF(stderr, "Image type: raw ppm format\n");
        break;
    }
    VPRINTF(stderr, "Full image: %dx%d\n", width, height);
    VPRINTF(stderr, "Maxval:     %d\n", maxval);
    if (do_alpha)
        VPRINTF(stderr, "Computing alpha channel...\n");
}