int DirectShowMediaType::bytesPerLine(const QVideoSurfaceFormat &format)
{
    switch (format.pixelFormat()) {
    // 32 bpp packed formats.
    case QVideoFrame::Format_RGB32:
    case QVideoFrame::Format_AYUV444:
        return format.frameWidth() * 4;
    // 24 bpp packed formats.
    case QVideoFrame::Format_RGB24:
        return PAD_TO_DWORD(format.frameWidth() * 3);
    // 16 bpp packed formats.
    case QVideoFrame::Format_RGB565:
    case QVideoFrame::Format_RGB555:
    case QVideoFrame::Format_YUYV:
    case QVideoFrame::Format_UYVY:
        return PAD_TO_DWORD(format.frameWidth() * 2);
    // Planar formats.
    case QVideoFrame::Format_IMC1:
    case QVideoFrame::Format_IMC2:
    case QVideoFrame::Format_IMC3:
    case QVideoFrame::Format_IMC4:
    case QVideoFrame::Format_YV12:
    case QVideoFrame::Format_NV12:
    case QVideoFrame::Format_YUV420P:
        return PAD_TO_DWORD(format.frameWidth());
    default:
        return 0;
    }
}