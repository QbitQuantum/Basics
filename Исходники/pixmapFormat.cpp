//typedef std::map<PixmapFormat::PixelFormat,unsigned int>::value_type value_type;
void PixmapFormat::init_depth_table(void)
{
    typedef std::map<PixelFormat,unsigned int>::value_type value_type;

    depth_table.insert(value_type(PixelFormat(PIXFMT_NONE), 0));
    
    depth_table.insert(value_type(PixelFormat(PIXFMT_RGB15_LE), 16));
    depth_table.insert(value_type(PixelFormat(PIXFMT_RGB16_LE), 16));
    depth_table.insert(value_type(PixelFormat(PIXFMT_RGB15_BE), 16));
    depth_table.insert(value_type(PixelFormat(PIXFMT_RGB16_BE), 16));
    

    depth_table.insert(value_type(PixelFormat(PIXFMT_BGR24), 24));
    depth_table.insert(value_type(PixelFormat(PIXFMT_BGR32), 32));
    depth_table.insert(value_type(PixelFormat(PIXFMT_RGB24), 24));
    depth_table.insert(value_type(PixelFormat(PIXFMT_RGB32), 32));

    depth_table.insert(value_type(PixelFormat(PIXFMT_YUYV),    16));
    depth_table.insert(value_type(PixelFormat(PIXFMT_YUV422P), 16));
    depth_table.insert(value_type(PixelFormat(PIXFMT_YUV420P),12));
    depth_table.insert(value_type(PixelFormat(PIXFMT_UYVY),    16));

    depth_table_initialized = true;

/*
    depth_table[PIXFMT_NONE]     = 0;

    depth_table[PIXFMT_RGB15_LE] = 16;
    depth_table[PIXFMT_RGB16_LE] = 16;
    depth_table[PIXFMT_RGB15_BE] = 16;
    depth_table[PIXFMT_RGB16_BE] = 16;

    depth_table[PIXFMT_BGR24]    = 24;
    depth_table[PIXFMT_BGR32]    = 32;
    depth_table[PIXFMT_RGB24]    = 24;
    depth_table[PIXFMT_RGB32]    = 32;

    depth_table[PIXFMT_YUYV]     = 16;
    depth_table[PIXFMT_YUV422P]  = 16;
    depth_table[PIXFMT_YUV420P]  = 12;

    depth_table[PIXFMT_UYVY]     = 16;
*/
}