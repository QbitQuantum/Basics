QDebug operator<<(QDebug dbg, const QVideoSurfaceFormat &f)
{
    QString typeName;
    switch (f.pixelFormat()) {
    case QVideoFrame::Format_Invalid:
        typeName = QLatin1String("Format_Invalid");
        break;
    case QVideoFrame::Format_ARGB32:
        typeName = QLatin1String("Format_ARGB32");
        break;
    case QVideoFrame::Format_ARGB32_Premultiplied:
        typeName = QLatin1String("Format_ARGB32_Premultiplied");
        break;
    case QVideoFrame::Format_RGB32:
        typeName = QLatin1String("Format_RGB32");
        break;
    case QVideoFrame::Format_RGB24:
        typeName = QLatin1String("Format_RGB24");
        break;
    case QVideoFrame::Format_RGB565:
        typeName = QLatin1String("Format_RGB565");
        break;
    case QVideoFrame::Format_RGB555:
        typeName = QLatin1String("Format_RGB555");
        break;
    case QVideoFrame::Format_ARGB8565_Premultiplied:
        typeName = QLatin1String("Format_ARGB8565_Premultiplied");
        break;
    case QVideoFrame::Format_BGRA32:
        typeName = QLatin1String("Format_BGRA32");
        break;
    case QVideoFrame::Format_BGRA32_Premultiplied:
        typeName = QLatin1String("Format_BGRA32_Premultiplied");
        break;
    case QVideoFrame::Format_BGR32:
        typeName = QLatin1String("Format_BGR32");
        break;
    case QVideoFrame::Format_BGR24:
        typeName = QLatin1String("Format_BGR24");
        break;
    case QVideoFrame::Format_BGR565:
        typeName = QLatin1String("Format_BGR565");
        break;
    case QVideoFrame::Format_BGR555:
        typeName = QLatin1String("Format_BGR555");
        break;
    case QVideoFrame::Format_BGRA5658_Premultiplied:
        typeName = QLatin1String("Format_BGRA5658_Premultiplied");
        break;
    case QVideoFrame::Format_AYUV444:
        typeName = QLatin1String("Format_AYUV444");
        break;
    case QVideoFrame::Format_AYUV444_Premultiplied:
        typeName = QLatin1String("Format_AYUV444_Premultiplied");
        break;
    case QVideoFrame::Format_YUV444:
        typeName = QLatin1String("Format_YUV444");
        break;
    case QVideoFrame::Format_YUV420P:
        typeName = QLatin1String("Format_YUV420P");
        break;
    case QVideoFrame::Format_YV12:
        typeName = QLatin1String("Format_YV12");
        break;
    case QVideoFrame::Format_UYVY:
        typeName = QLatin1String("Format_UYVY");
        break;
    case QVideoFrame::Format_YUYV:
        typeName = QLatin1String("Format_YUYV");
        break;
    case QVideoFrame::Format_NV12:
        typeName = QLatin1String("Format_NV12");
        break;
    case QVideoFrame::Format_NV21:
        typeName = QLatin1String("Format_NV21");
        break;
    case QVideoFrame::Format_IMC1:
        typeName = QLatin1String("Format_IMC1");
        break;
    case QVideoFrame::Format_IMC2:
        typeName = QLatin1String("Format_IMC2");
        break;
    case QVideoFrame::Format_IMC3:
        typeName = QLatin1String("Format_IMC3");
        break;
    case QVideoFrame::Format_IMC4:
        typeName = QLatin1String("Format_IMC4");
        break;
    case QVideoFrame::Format_Y8:
        typeName = QLatin1String("Format_Y8");
        break;
    case QVideoFrame::Format_Y16:
        typeName = QLatin1String("Format_Y16");
    default:
        typeName = QString(QLatin1String("UserType(%1)" )).arg(int(f.pixelFormat()));
    }

    dbg.nospace() << "QVideoSurfaceFormat(" << typeName;
    dbg.nospace() << ", " << f.frameSize();
    dbg.nospace() << ", viewport=" << f.viewport();
    dbg.nospace() << ", pixelAspectRatio=" << f.pixelAspectRatio();
    dbg.nospace() << ")";

    foreach(const QByteArray& propertyName, f.propertyNames())
        dbg << "\n    " << propertyName.data() << " = " << f.property(propertyName.data());

    return dbg.space();
}