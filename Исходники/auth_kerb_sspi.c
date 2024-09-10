static apr_status_t
cleanup_sec_buffer(void *data)
{
    FreeContextBuffer(data);

    return APR_SUCCESS;
}