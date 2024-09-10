QString ZBarReaderTest::decode(const QImage &image)
{
    Image zbarImg(image.width(), image.height(), "Y800", image.bits(), image.bytesPerLine() * image.height());

    QString line;
    ImageScanner scanner;
    scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1);
    scanner.scan(zbarImg);

    SymbolSet s = scanner.get_results();
    int resSize = s.get_size();
    if (resSize > 0) {
        mTotalRead++;
        for (SymbolIterator symbol = scanner.get_results().symbol_begin(); symbol != scanner.get_results().symbol_end(); ++symbol) {
            if (QString::compare("QR-Code ", QString(symbol->get_type_name().data()).trimmed()))
                line += " | " + QString(symbol->get_data().data()).replace("\n", "<br>");
        }
    }
    return line;
}