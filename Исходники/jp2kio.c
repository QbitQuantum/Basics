static OPJ_SIZE_T
opj_write_from_file(void *p_buffer, OPJ_SIZE_T p_nb_bytes, FILE *fp)
{
    return fwrite(p_buffer, 1, p_nb_bytes, fp);
}