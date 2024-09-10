    PixelFormat GL3PlusPixelUtil::getClosestOGREFormat(GLenum format)
    {
        switch(format)
        {
        case GL_DEPTH_COMPONENT24:
        case GL_DEPTH_COMPONENT32:
        case GL_DEPTH_COMPONENT32F:
        case GL_DEPTH_COMPONENT:
            return PF_DEPTH;
        case GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT:
            return PF_DXT1;
        case GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT:
            return PF_DXT3;
        case GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT:
            return PF_DXT5;
        case GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM_ARB:
            return PF_BC7_UNORM;
        case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4_KHR:
        case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x4_KHR:
        case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5_KHR:
        case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x5_KHR:
        case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6_KHR:
        case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x5_KHR:
        case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x6_KHR:
        case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x8_KHR:
        case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x5_KHR:
        case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x6_KHR:
        case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x8_KHR:
        case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x10_KHR:
        case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x10_KHR:
        case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x12_KHR:
            return PixelFormat(int(PF_ASTC_RGBA_4X4_LDR) +
                               (format - GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4_KHR));
        case GL_SRGB8:
        case GL_RGB8: // prefer native endian byte format
            return PF_BYTE_RGB;
        case GL_SRGB8_ALPHA8:
        case GL_RGBA8: // prefer native endian byte format
            return PF_BYTE_RGBA;
        };

        for(int pf = 0; pf < PF_COUNT; pf++) {
            if(_pixelFormats[pf].internalFormat == format)
                return (PixelFormat)pf;
        }

        return PF_BYTE_RGBA;
    }