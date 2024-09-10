/*
 * Function:    compress_buffer
 * Purpose:     Compress the buffer.
 * Returns:     Z_OK            - success
 *              Z_MEM_ERROR     - not enough memory
 *              Z_BUF_ERROR     - not enough room in the output buffer
 *              Z_STREAM_ERROR  - level parameter is invalid
 * Programmer:  Bill Wendling, 05. June 2002
 * Modifications:
 */
static void
compress_buffer(Bytef *dest, uLongf *destLen, const Bytef *source,
                uLong sourceLen)
{
    int rc = compress2(dest, destLen, source, sourceLen, compress_level);

    if (rc != Z_OK) {
        /* compress2 failed - cleanup and tell why */
        cleanup();

        switch (rc) {
        case Z_MEM_ERROR:
            error("not enough memory");
            break;
        case Z_BUF_ERROR:
            error("not enough room in the output buffer");
            break;
        case Z_STREAM_ERROR:
            error("level parameter (%d) is invalid", compress_level);
            break;
        default:
            error("unknown compression error");
            break;
        }
    }
}