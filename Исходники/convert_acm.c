void
acm_cv_convert (const converter_fmt_t *cfmt, u_char *state, sample *src_buf, int src_len, sample *dst_buf, int dst_len)
{
        ACMSTREAMHEADER ash;
        LPHACMSTREAM    lphs;

        UNUSED(cfmt);

        memset(&ash, 0, sizeof(ash));
        ash.cbStruct        = sizeof(ash);
        ash.pbSrc           = (LPBYTE)src_buf;
        ash.cbSrcLength     = src_len * sizeof(sample);
        ash.pbDst           = (LPBYTE)dst_buf;
        ash.cbDstLength     = dst_len * sizeof(sample);

        lphs = (LPHACMSTREAM)state;

        if (acmStreamPrepareHeader(*lphs, &ash, 0) ||
            acmStreamConvert(*lphs, &ash, ACM_STREAMCONVERTF_BLOCKALIGN)) {
                memset(dst_buf, 0, dst_len * sizeof(sample));
        }
        return;
}