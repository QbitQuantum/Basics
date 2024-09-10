bool videoFormatToGL(const VideoFormat& fmt, GLint* internal_format, GLenum* data_format, GLenum* data_type, QMatrix4x4* mat)
{
    typedef struct fmt_entry {
        VideoFormat::PixelFormat pixfmt;
        GLint internal_format;
        GLenum format;
        GLenum type;
    } fmt_entry;
    static const fmt_entry pixfmt_to_gles[] = {
        {VideoFormat::Format_BGRA32, GL_BGRA, GL_BGRA, GL_UNSIGNED_BYTE }, //tested for angle
        {VideoFormat::Format_RGB32,  GL_BGRA, GL_BGRA, GL_UNSIGNED_BYTE },
        {VideoFormat::Format_Invalid, 0, 0, 0}
    };
    Q_UNUSED(pixfmt_to_gles);
    static const fmt_entry pixfmt_to_desktop[] = {
        {VideoFormat::Format_BGRA32, GL_RGBA, GL_BGRA, GL_UNSIGNED_BYTE }, //bgra bgra works on win but not osx
        {VideoFormat::Format_RGB32,  GL_RGBA, GL_BGRA, GL_UNSIGNED_BYTE }, //FIXMEL endian check
        //{VideoFormat::Format_BGRA32,  GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE }, //{2,1,0,3}
        //{VideoFormat::Format_BGR24,   GL_RGB,  GL_BGR,  GL_UNSIGNED_BYTE }, //{0,1,2,3}
    #ifdef GL_UNSIGNED_SHORT_5_6_5_REV
        {VideoFormat::Format_BGR565, GL_RGB,  GL_RGB,  GL_UNSIGNED_SHORT_5_6_5_REV}, // es error, use channel map
    #endif
    #ifdef GL_UNSIGNED_SHORT_1_5_5_5_REV
        {VideoFormat::Format_RGB555, GL_RGBA, GL_BGRA, GL_UNSIGNED_SHORT_1_5_5_5_REV},
    #endif
    #ifdef GL_UNSIGNED_SHORT_1_5_5_5_REV
        {VideoFormat::Format_BGR555, GL_RGBA, GL_RGBA, GL_UNSIGNED_SHORT_1_5_5_5_REV},
    #endif
        // TODO: BE formats not implemeted
        {VideoFormat::Format_RGB48, GL_RGB, GL_RGB, GL_UNSIGNED_SHORT }, //TODO: they are not work for ANGLE, and rgb16 works on desktop gl, so remove these lines to use rgb16?
        {VideoFormat::Format_RGB48LE, GL_RGB, GL_RGB, GL_UNSIGNED_SHORT },
        {VideoFormat::Format_RGB48BE, GL_RGB, GL_RGB, GL_UNSIGNED_SHORT },
        {VideoFormat::Format_BGR48, GL_RGB, GL_BGR, GL_UNSIGNED_SHORT }, //RGB16?
        {VideoFormat::Format_BGR48LE, GL_RGB, GL_BGR, GL_UNSIGNED_SHORT },
        {VideoFormat::Format_BGR48BE, GL_RGB, GL_BGR, GL_UNSIGNED_SHORT },
        {VideoFormat::Format_RGBA64LE, GL_RGBA, GL_RGBA, GL_UNSIGNED_SHORT },
        {VideoFormat::Format_RGBA64BE, GL_RGBA, GL_RGBA, GL_UNSIGNED_SHORT },
        {VideoFormat::Format_BGRA64LE, GL_RGBA, GL_BGRA, GL_UNSIGNED_SHORT },
        {VideoFormat::Format_BGRA64BE, GL_RGBA, GL_BGRA, GL_UNSIGNED_SHORT },
        {VideoFormat::Format_Invalid, 0, 0, 0}
    };
    Q_UNUSED(pixfmt_to_desktop);
    const fmt_entry *pixfmt_gl_entry = pixfmt_to_desktop;
    if (OpenGLHelper::isOpenGLES())
        pixfmt_gl_entry = pixfmt_to_gles;
    // Very special formats, for which OpenGL happens to have direct support
    static const fmt_entry pixfmt_gl_base[] = {
        {VideoFormat::Format_RGBA32, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE }, // only tested for osx, win, angle
        {VideoFormat::Format_RGB24,  GL_RGB,  GL_RGB,  GL_UNSIGNED_BYTE },
        {VideoFormat::Format_RGB565, GL_RGB,  GL_RGB,  GL_UNSIGNED_SHORT_5_6_5},
        {VideoFormat::Format_BGR32,  GL_BGRA, GL_BGRA, GL_UNSIGNED_BYTE }, //rgba(tested) or abgr, depending on endian
    };
    const VideoFormat::PixelFormat pixfmt = fmt.pixelFormat();
    // can not use array size because pixfmt_gl_entry is set on runtime
    for (const fmt_entry* e = pixfmt_gl_entry; e->pixfmt != VideoFormat::Format_Invalid; ++e) {
        if (e->pixfmt == pixfmt) {
            *internal_format = e->internal_format;
            *data_format = e->format;
            *data_type = e->type;
            if (mat)
                *mat = QMatrix4x4();
            return true;
        }
    }
    for (size_t i = 0; i < ARRAY_SIZE(pixfmt_gl_base); ++i) {
        const fmt_entry& e = pixfmt_gl_base[i];
        if (e.pixfmt == pixfmt) {
            *internal_format = e.internal_format;
            *data_format = e.format;
            *data_type = e.type;
            if (mat)
                *mat = QMatrix4x4();
            return true;
        }
    }
    static const fmt_entry pixfmt_to_gl_swizzele[] = {
        {VideoFormat::Format_UYVY, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE },
        {VideoFormat::Format_YUYV, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE },
        {VideoFormat::Format_VYUY, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE },
        {VideoFormat::Format_YVYU, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE },
        {VideoFormat::Format_BGR565, GL_RGB,  GL_RGB,  GL_UNSIGNED_SHORT_5_6_5}, //swizzle
        {VideoFormat::Format_RGB555, GL_RGBA, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1}, //not working
        {VideoFormat::Format_BGR555, GL_RGBA, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1}, //not working
    };
    for (size_t i = 0; i < ARRAY_SIZE(pixfmt_to_gl_swizzele); ++i) {
        const fmt_entry& e = pixfmt_to_gl_swizzele[i];
        if (e.pixfmt == pixfmt) {
            *internal_format = e.internal_format;
            *data_format = e.format;
            *data_type = e.type;
            if (mat)
                *mat = channelMap(fmt);
            return true;
        }
    }
    GLint *i_f = internal_format;
    GLenum *d_f = data_format;
    GLenum *d_t = data_type;
    gl_param_t* gp = (gl_param_t*)get_gl_param();
    if (gp == gl_param_desktop && (
                fmt.planeCount() == 2 // nv12 UV plane is 16bit, but we use rg
                || (OpenGLHelper::depth16BitTexture() == 16 && OpenGLHelper::has16BitTexture() && fmt.isBigEndian() && fmt.bitsPerComponent() > 8) // 16bit texture does not support be channel now
                )) {
        gp = (gl_param_t*)gl_param_desktop_fallback;
        qDebug("desktop_fallback for %s", fmt.planeCount() == 2 ? "bi-plane format" : "16bit big endian channel");
    }
    for (int p = 0; p < fmt.planeCount(); ++p) {
        // for packed rgb(swizzle required) and planar formats
        const int c = (fmt.channels(p)-1) + 4*((fmt.bitsPerComponent() + 7)/8 - 1);
        if (gp[c].format == 0)
            return false;
        const gl_param_t& f = gp[c];
        *(i_f++) = f.internal_format;
        *(d_f++) = f.format;
        *(d_t++) = f.type;
    }
    if (mat)
        *mat = channelMap(fmt);
    return true;
}