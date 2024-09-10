QString KXFace::fromImage(const QImage &image)
{
    if(image.isNull())
        return QString::null;

    QImage scaledImg = image.smoothScale(48, 48);
    QByteArray ba;
    QBuffer buffer(ba);
    buffer.open(IO_WriteOnly);
    scaledImg.save(&buffer, "XBM");
    QString xbm(ba);
    xbm.remove(0, xbm.find("{") + 1);
    xbm.truncate(xbm.find("}"));
    xbm.remove(" ");
    xbm.remove(",");
    xbm.remove("0x");
    xbm.remove("\n");
    xbm.truncate(576);
    QCString tmp = QCString(xbm.latin1());
    uint len = tmp.length();
    for(uint i = 0; i < len; ++i)
    {
        switch(tmp[i])
        {
            case '1':
                tmp[i] = '8';
                break;
            case '2':
                tmp[i] = '4';
                break;
            case '3':
                tmp[i] = 'c';
                break;
            case '4':
                tmp[i] = '2';
                break;
            case '5':
                tmp[i] = 'a';
                break;
            case '7':
                tmp[i] = 'e';
                break;
            case '8':
                tmp[i] = '1';
                break;
            case 'A':
            case 'a':
                tmp[i] = '5';
                break;
            case 'B':
            case 'b':
                tmp[i] = 'd';
                break;
            case 'C':
            case 'c':
                tmp[i] = '3';
                break;
            case 'D':
            case 'd':
                tmp[i] = 'b';
                break;
            case 'E':
            case 'e':
                tmp[i] = '7';
                break;
        }
        if(i % 2)
        {
            char t = tmp[i];
            tmp[i] = tmp[i - 1];
            tmp[i - 1] = t;
        }
    }
    tmp.replace(QRegExp("(\\w{12})"), "\\1\n");
    tmp.replace(QRegExp("(\\w{4})"), "0x\\1,");
    len = tmp.length();
    char *fbuf = (char *)malloc(len + 1);
    strncpy(fbuf, (const char *)tmp, len);
    fbuf[len] = '\0';
    if(!(status = setjmp(comp_env)))
    {
        ReadFace(fbuf);
        GenFace();
        CompAll(fbuf);
    }
    QString ret(fbuf);
    free(fbuf);

    return ret;
}