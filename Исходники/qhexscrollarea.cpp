void QHexScrollArea::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)

    QPainter painter;
    painter.begin(viewport());
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::TextAntialiasing, true);

    painter.fillRect(0,0,width(), height(), QBrush(0xD7D7AF));

    QFont font = this->font();
    QFontMetrics fm = this->fontMetrics();

    painter.setFont(font);

    int ssw = fm.width(" ");                                                // width of space symbol
    int zsw = fm.width("0");                                                // width of zero symbol

    int div = maxDataCount / bytesPerRow;                                   // data size divide to 16. number of maximum rows
    int mod = maxDataCount % bytesPerRow;                                   // data size module to 16. number of bytes at last row

    maxRowsCount = div;
    if (mod > 0) maxRowsCount += 1;

    int rowNumberW = 2 * ssw + fm.width(QString::number(maxRowsCount));     // width of row number column
    int rowNumberH = viewport()->height();                                  // height of row number column

    // painting lines number column background
    painter.fillRect(0, 0, rowNumberW, rowNumberH, QBrush(0xD4D0C8));
    painter.fillRect(getRowNumberWidth(), 0, getByteNumberWidth(), height(), QBrush(QColor(0xAFAF87)));
    painter.fillRect(getRowNumberWidth(), 0, width(), fm.height()+4, QBrush(QColor(0xAFAF87)));

    // number of rows visible on viewport
    int viewportRow = (int) ceil( (double)(viewport()->height() - (double)fm.height() ) / (double)fm.height() );

    // updating verticalScrollBar settings
    verticalScrollBar()->setMinimum(0);

    if (maxRowsCount > viewportRow)
    {
        verticalScrollBar()->setMaximum( (maxRowsCount - viewportRow) + 1);
    }
    else
    {
        verticalScrollBar()->setMaximum(0);
    }

    verticalScrollBar()->setPageStep(10);
    verticalScrollBar()->setSingleStep(1);

    int vsbValue = verticalScrollBar()->value();
    int hsbValue = horizontalScrollBar()->value();
    Q_UNUSED(hsbValue)

    font.setBold(false);
    painter.setFont(font);

    // painting header
    painter.setPen(0x5F5F00);
    int x = rowNumberW+zsw*8 + ssw*2;
    int y = fm.height();
    painter.drawText(x, y, " 00 01 02 03  04 05 06 07   08 09 0A 0B  0C 0D 0E 0F                     ");

    qint64 minLine = vsbValue;                                          // minimum visible line number
    qint64 maxLine = vsbValue + viewportRow;                            // maximum visible line number

    if (maxRowsCount < maxLine)
        maxLine = maxRowsCount;

    qint64 minData = minLine * bytesPerRow;                             // minimum visible byte
    qint64 maxData = maxLine * bytesPerRow;                             // maximum visible data

    if ( maxData > maxDataCount)
    {
        maxData = maxDataCount;
    }

    QByteArray buffer;
    emit fillBuffer(buffer, minData, maxData);

    for (qint64 i = minLine; i < maxLine; i++)
    {
        quint32 x = zsw;
        quint32 y = (i-vsbValue+1)*fm.height() + fm.height();

        QByteArray data = buffer.mid( (int)( i - minLine ) * 16, 16);

        QString line = QString::number(i);
//       int length = 9-line.length();
        int length = QString::number(maxRowsCount).length() - QString::number(i).length();
        for (int j=0; j<length; j++)
            line.prepend(" ");
        if (mShowUpperLine) line = line.toUpper();

        /* bytes number and filling 0 to start*/
        QString bytes = QString::number(i*bytesPerRow,16);
        length = 8-bytes.length();
        for (int j=0; j<length; j++)
            bytes.prepend("0");
        if (mShowUpperData)
            bytes = bytes.toUpper();

        /* data hex string */
        QString h = QString("%1 %2 %3 %4  %5 %6 %7 %8   %9 %10 %11 %12  %13 %14 %15 %16")
                .arg(QString(data.mid(0x00, 1).toHex()))
                .arg(QString(data.mid(0x01, 1).toHex()))
                .arg(QString(data.mid(0x02, 1).toHex()))
                .arg(QString(data.mid(0x03, 1).toHex()))
                .arg(QString(data.mid(0x04, 1).toHex()))
                .arg(QString(data.mid(0x05, 1).toHex()))
                .arg(QString(data.mid(0x06, 1).toHex()))
                .arg(QString(data.mid(0x07, 1).toHex()))
                .arg(QString(data.mid(0x08, 1).toHex()))
                .arg(QString(data.mid(0x09, 1).toHex()))
                .arg(QString(data.mid(0x0A, 1).toHex()))
                .arg(QString(data.mid(0x0B, 1).toHex()))
                .arg(QString(data.mid(0x0C, 1).toHex()))
                .arg(QString(data.mid(0x0D, 1).toHex()))
                .arg(QString(data.mid(0x0E, 1).toHex()))
                .arg(QString(data.mid(0x0F, 1).toHex()));
         h = h.toLower();

        /* data char string */
        QString c;
        for (int j=0; j < data.size(); j++)
        {
            c.append(QChar(data.at(j)).isPrint() ? QChar(data.at(j)) : '.');
        }

        /* drawing row number */
        font.setBold(true);
        painter.setFont(font);
        painter.setPen(0x5F5F00);
        painter.drawText(x, y, line);

        /* drawing data sequence number */
        x = rowNumberW + zsw;
        font.setBold(false);
        painter.setFont(font);
        painter.setPen(0x5F5F00);
        painter.drawText(x, y, bytes);

        /* drawing data */
        x = x + zsw*8 + ssw*2;
        painter.setPen(0x5F5F00);
        painter.drawText(x, y, h);
        x += zsw*32 + ssw*22;
        painter.drawText(x, y, c);
    }

    // paint selection

    painter.setRenderHint(QPainter::Antialiasing, false);

    if (selectedByte != -1)
    {
        quint32 cn = selectedByte % bytesPerRow;                           // column number
        quint32 rn = selectedByte / bytesPerRow;                           // row number

        quint32 sel_x = rowNumberW + zsw * 8 + ssw * 3;
        sel_x -=  ssw / 2;

        if (cn >= 0 && cn <= 3)
            sel_x += cn * zsw * 3;
        if (cn >= 4 && cn <= 7)
            sel_x += cn * zsw * 3 + zsw * 1;
        if (cn >= 8 && cn <= 11)
            sel_x += cn * zsw * 3 + zsw * 3;
        if (cn >= 12 && cn <= 15)
            sel_x += cn * zsw * 3 + zsw * 4;

        quint32 rw = ssw * 3 - 2;                                           // selected rectange width

        quint32 sel_y = 0;
        if (minLine <= rn && rn <= maxLine)
        {
            rn -= minLine;
            sel_y = fm.height() * (rn+1);
        }
        else
        {
            sel_y = -100;
        }

        QBrush brush(QColor(0x00, 0xff, 0xff, 100));
        painter.fillRect(sel_x, sel_y+4, rw, 18, brush);           // painting selected byte
        painter.drawRect(sel_x, sel_y+4, rw, 18);                       // painting selected byte
    }

//    paintSelections(painter);

//    paintSelection(painter);

//    paintBlinking(painter);

    painter.end();
}