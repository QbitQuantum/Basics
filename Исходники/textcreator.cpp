bool TextCreator::create(const QString &path, int width, int height, QImage &img)
{
    // Filter out unwanted mimetypes
    KMimeType::Ptr mimeType = KMimeType::findByPath(path);
    if(mimeType->is("text/rtf"))
        return false;

    if(!m_splitter)
    {
        m_splitter = new KPixmapSplitter;
        QString pixmap = locate("data", "konqueror/pics/thumbnailfont_7x4.png");
        if(!pixmap.isEmpty())
        {
            // FIXME: make font/glyphsize configurable...
            m_splitter->setPixmap(QPixmap(pixmap));
            m_splitter->setItemSize(QSize(4, 7));
        }
    }

    bool ok = false;

    // determine some sizes...
    // example: width: 60, height: 64
    QSize pixmapSize(width, height);
    if(height * 3 > width * 4)
        pixmapSize.setHeight(width * 4 / 3);
    else
        pixmapSize.setWidth(height * 3 / 4);

    if(pixmapSize != m_pixmap.size())
        m_pixmap.resize(pixmapSize);

    // one pixel for the rectangle, the rest. whitespace
    int xborder = 1 + pixmapSize.width() / 16;  // minimum x-border
    int yborder = 1 + pixmapSize.height() / 16; // minimum y-border

    QSize chSize = m_splitter->itemSize(); // the size of one char
    int xOffset = chSize.width();
    int yOffset = chSize.height();

    // calculate a better border so that the text is centered
    int canvasWidth = pixmapSize.width() - 2 * xborder;
    int canvasHeight = pixmapSize.height() - 2 * yborder;
    int numCharsPerLine = (int)(canvasWidth / chSize.width());
    int numLines = (int)(canvasHeight / chSize.height());

    // assumes an average line length of <= 120 chars
    const int bytesToRead = 120 * numLines;

    // create text-preview
    QFile file(path);
    if(file.open(IO_ReadOnly))
    {
        if(!m_data || m_dataSize < bytesToRead + 1)
        {
            delete[] m_data;
            m_data = new char[bytesToRead + 1];
            m_dataSize = bytesToRead + 1;
        }

        int read = file.readBlock(m_data, bytesToRead);
        if(read > 0)
        {
            ok = true;
            m_data[read] = '\0';
            QString text = QString::fromLocal8Bit(m_data);
            // FIXME: maybe strip whitespace and read more?

            m_pixmap.fill(QColor(245, 245, 245)); // light-grey background

            QRect rect;

            int rest = m_pixmap.width() - (numCharsPerLine * chSize.width());
            xborder = QMAX(xborder, rest / 2); // center horizontally
            rest = m_pixmap.height() - (numLines * chSize.height());
            yborder = QMAX(yborder, rest / 2); // center vertically
            // end centering

            int x = xborder, y = yborder; // where to paint the characters
            int posNewLine = m_pixmap.width() - (chSize.width() + xborder);
            int posLastLine = m_pixmap.height() - (chSize.height() + yborder);
            bool newLine = false;
            Q_ASSERT(posNewLine > 0);
            const QPixmap *fontPixmap = &(m_splitter->pixmap());

            for(uint i = 0; i < text.length(); i++)
            {
                if(x > posNewLine || newLine) // start a new line?
                {
                    x = xborder;
                    y += yOffset;

                    if(y > posLastLine) // more text than space
                        break;

                    // after starting a new line, we also jump to the next
                    // physical newline in the file if we don't come from one
                    if(!newLine)
                    {
                        int pos = text.find('\n', i);
                        if(pos == -1)
                            break;
                        i = pos + 1;
                    }

                    newLine = false;
                }

                // check for newlines in the text (unix,dos)
                QChar ch = text.at(i);
                if(ch == '\n')
                {
                    newLine = true;
                    continue;
                }
                else if(ch == '\r' && text.at(i + 1) == '\n')
                {
                    newLine = true;
                    i++; // skip the next character (\n) as well
                    continue;
                }

                rect = m_splitter->coordinates(ch);
                if(!rect.isEmpty())
                {
                    bitBlt(&m_pixmap, QPoint(x, y), fontPixmap, rect, Qt::CopyROP);
                }

                x += xOffset; // next character
            }
            if(ok)
                img = m_pixmap.convertToImage();
        }

        file.close();
    }
    return ok;
}