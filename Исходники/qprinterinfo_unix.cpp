// solaris, not 2.6
void qt_parseEtcLpPrinters(QList<QPrinterDescription> *printers)
{
    QDir lp(QLatin1String("/etc/lp/printers"));
    QFileInfoList dirs = lp.entryInfoList();
    if (dirs.isEmpty())
        return;

    QString tmp;
    for (int i = 0; i < dirs.size(); ++i) {
        QFileInfo printer = dirs.at(i);
        if (printer.isDir()) {
            tmp.sprintf("/etc/lp/printers/%s/configuration",
                         printer.fileName().toAscii().data());
            QFile configuration(tmp);
            char *line = new char[1025];
            QString remote(QLatin1String("Remote:"));
            QString contentType(QLatin1String("Content types:"));
            QString printerHost;
            bool canPrintPostscript = false;
            if (configuration.open(QIODevice::ReadOnly)) {
                while (!configuration.atEnd() &&
                        configuration.readLine(line, 1024) > 0) {
                    if (QString::fromLatin1(line).startsWith(remote)) {
                        const char *p = line;
                        while (*p != ':')
                            p++;
                        p++;
                        while (isspace((uchar) *p))
                            p++;
                        printerHost = QString::fromLocal8Bit(p);
                        printerHost = printerHost.simplified();
                    } else if (QString::fromLatin1(line).startsWith(contentType)) {
                        char *p = line;
                        while (*p != ':')
                            p++;
                        p++;
                        char *e;
                        while (*p) {
                            while (isspace((uchar) *p))
                                p++;
                            if (*p) {
                                char s;
                                e = p;
                                while (isalnum((uchar) *e))
                                    e++;
                                s = *e;
                                *e = '\0';
                                if (!qstrcmp(p, "postscript") ||
                                     !qstrcmp(p, "any"))
                                    canPrintPostscript = true;
                                *e = s;
                                if (s == ',')
                                    e++;
                                p = e;
                            }
                        }
                    }
                }
                if (canPrintPostscript)
                    qt_perhapsAddPrinter(printers, printer.fileName(),
                                         printerHost, QLatin1String(""));
            }
            delete[] line;
        }
    }
}