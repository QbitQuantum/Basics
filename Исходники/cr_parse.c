jxrc_t_pixelFormat jxrc_image_pixelformat(jxr_container_t container, int imagenum)
{
    unsigned char guid[16];
    int i;
    assert(imagenum < container->image_count);

    unsigned ifd_cnt = container->table_cnt[imagenum];
    struct ifd_table*ifd = container->table[imagenum];

    unsigned idx;
    for (idx = 0 ; idx < ifd_cnt ; idx += 1) {
        if (ifd[idx].tag == 0xbc01)
            break;
    }

    assert(idx < ifd_cnt);
    assert(ifd[idx].tag == 0xbc01);
    assert(ifd[idx].cnt == 16);
    memcpy(guid, ifd[idx].value_.p_byte, 16);
    for(i=0; i< NUM_GUIDS; i++)
    {
        if(isEqualGUID(guid, jxr_guids[i]))
        {
            break;
        }
    }
    if(i==NUM_GUIDS)
        assert(0);
    return (jxrc_t_pixelFormat)i;
    
}