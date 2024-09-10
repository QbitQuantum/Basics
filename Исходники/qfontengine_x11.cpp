static QFontEngine::FaceId fontFile(const QByteArray &_xname, QFreetypeFace **freetype, int *synth)
{
    *freetype = 0;
    *synth = 0;

    QByteArray xname = _xname.toLower();

    int pos = 0;
    int minus = 0;
    while (minus < 5 && (pos = xname.indexOf('-', pos + 1)))
        ++minus;
    QByteArray searchname = xname.left(pos);
    while (minus < 12 && (pos = xname.indexOf('-', pos + 1)))
        ++minus;
    QByteArray encoding = xname.mid(pos + 1);
    //qDebug("xname='%s', searchname='%s', encoding='%s'", xname.data(), searchname.data(), encoding.data());
    QStringList fontpath = fontPath();
    QFontEngine::FaceId face_id;
    face_id.index = 0;

    QByteArray best_mapping;

    for (QStringList::ConstIterator it = fontpath.constBegin(); it != fontpath.constEnd(); ++it) {
        if (!(*it).startsWith(QLatin1Char('/')))
            continue; // not a path name, a font server
        QString fontmapname;
        int num = 0;
        // search font.dir and font.scale for the right file
        while (num < 2) {
            if (num == 0)
                fontmapname = (*it) + QLatin1String("/fonts.scale");
            else
                fontmapname = (*it) + QLatin1String("/fonts.dir");
            ++num;
            //qWarning(fontmapname);
            QFile fontmap(fontmapname);
            if (!fontmap.open(QIODevice::ReadOnly))
                continue;
            while (!fontmap.atEnd()) {
                QByteArray mapping = fontmap.readLine();
                QByteArray lmapping = mapping.toLower();

                //qWarning(xfontname);
                //qWarning(mapping);
                if (!lmapping.contains(searchname))
                    continue;
                int index = mapping.indexOf(' ');
                QByteArray ffn = mapping.mid(0,index);
                // remove bitmap formats freetype can't handle
                if (ffn.contains(".spd") || ffn.contains(".phont"))
                    continue;
                bool best_match = false;
                if (!best_mapping.isEmpty()) {
                    if (lmapping.contains("-0-0-0-0-")) { // scalable font
                        best_match = true;
                        goto found;
                    }
                    if (lmapping.contains(encoding) && !best_mapping.toLower().contains(encoding))
                        goto found;
                    continue;
                }

            found:
                int colon = ffn.lastIndexOf(':');
                if (colon != -1) {
                    QByteArray s = ffn.left(colon);
                    ffn = ffn.mid(colon + 1);
                    if (s.contains("ds="))
                        *synth |= QFontEngine::SynthesizedBold;
                    if (s.contains("ai="))
                        *synth |= QFontEngine::SynthesizedItalic;
                }
                face_id.filename = (*it).toLocal8Bit() + '/' + ffn;
                best_mapping = mapping;
                if (best_match)
                    goto end;
            }
        }
    }
end:
//     qDebug("fontfile for %s is from '%s'\n    got %s synth=%d", xname.data(),
//            best_mapping.data(), face_id.filename.data(), *synth);
    *freetype = QFreetypeFace::getFace(face_id);
    if (!*freetype) {
        face_id.index = 0;
        face_id.filename = QByteArray();
    }
    return face_id;
}