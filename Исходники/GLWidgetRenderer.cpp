bool videoFormatToGL(const VideoFormat& fmt, GLint* internal_format, GLenum* data_format, GLenum* data_type)
{
    struct fmt_entry {
        VideoFormat::PixelFormat pixfmt;
        GLint internal_format;
        GLenum format;
        GLenum type;
    };
    // Very special formats, for which OpenGL happens to have direct support
    static const struct fmt_entry pixfmt_to_gl_formats[] = {
#ifdef QT_OPENGL_ES_2
        {VideoFormat::Format_ARGB32, GL_BGRA, GL_BGRA, GL_UNSIGNED_BYTE },
        {VideoFormat::Format_RGB32,  GL_BGRA, GL_BGRA, GL_UNSIGNED_BYTE },
#else
        {VideoFormat::Format_RGB32,  GL_RGBA, GL_BGRA, GL_UNSIGNED_BYTE },
        {VideoFormat::Format_ARGB32, GL_RGBA, GL_BGRA, GL_UNSIGNED_BYTE },
#endif
        {VideoFormat::Format_RGB24,  GL_RGB,  GL_RGB,  GL_UNSIGNED_BYTE },
    #ifdef GL_UNSIGNED_SHORT_1_5_5_5_REV
        {VideoFormat::Format_RGB555, GL_RGBA, GL_BGRA, GL_UNSIGNED_SHORT_1_5_5_5_REV},
    #endif
        {VideoFormat::Format_RGB565, GL_RGB,  GL_RGB,  GL_UNSIGNED_SHORT_5_6_5}, //GL_UNSIGNED_SHORT_5_6_5_REV?
        //{VideoFormat::Format_BGRA32, GL_RGBA, GL_BGRA, GL_UNSIGNED_BYTE },
        //{VideoFormat::Format_BGR32,  GL_BGRA, GL_BGRA, GL_UNSIGNED_BYTE },
        {VideoFormat::Format_BGR24,  GL_RGB,  GL_BGR,  GL_UNSIGNED_BYTE },
    #ifdef GL_UNSIGNED_SHORT_1_5_5_5_REV
        {VideoFormat::Format_BGR555, GL_RGBA, GL_BGRA, GL_UNSIGNED_SHORT_1_5_5_5_REV},
    #endif
        {VideoFormat::Format_BGR565, GL_RGB,  GL_RGB,  GL_UNSIGNED_SHORT_5_6_5}, // need swap r b?
    };

    for (unsigned int i = 0; i < sizeof(pixfmt_to_gl_formats)/sizeof(pixfmt_to_gl_formats[0]); ++i) {
        if (pixfmt_to_gl_formats[i].pixfmt == fmt.pixelFormat()) {
            *internal_format = pixfmt_to_gl_formats[i].internal_format;
            *data_format = pixfmt_to_gl_formats[i].format;
            *data_type = pixfmt_to_gl_formats[i].type;
            return true;
        }
    }
    return false;
}