void QTextOdfWriter::writeBlock(QXmlStreamWriter &writer, const QTextBlock &block)
{
    if (block.textList()) { // its a list-item
        const int listLevel = block.textList()->format().indent();
        if (m_listStack.isEmpty() || m_listStack.top() != block.textList()) {
            // not the same list we were in.
            while (m_listStack.count() >= listLevel && !m_listStack.isEmpty() && m_listStack.top() != block.textList() ) { // we need to close tags
                m_listStack.pop();
                writer.writeEndElement(); // list
                if (m_listStack.count())
                    writer.writeEndElement(); // list-item
            }
            while (m_listStack.count() < listLevel) {
                if (m_listStack.count())
                    writer.writeStartElement(textNS, QString::fromLatin1("list-item"));
                writer.writeStartElement(textNS, QString::fromLatin1("list"));
                if (m_listStack.count() == listLevel - 1) {
                    m_listStack.push(block.textList());
                    writer.writeAttribute(textNS, QString::fromLatin1("style-name"), QString::fromLatin1("L%1")
                            .arg(block.textList()->formatIndex()));
                }
                else {
                    m_listStack.push(0);
                }
            }
        }
        writer.writeStartElement(textNS, QString::fromLatin1("list-item"));
    }
    else {
        while (! m_listStack.isEmpty()) {
            m_listStack.pop();
            writer.writeEndElement(); // list
            if (m_listStack.count())
                writer.writeEndElement(); // list-item
        }
    }

    if (block.length() == 1) { // only a linefeed
        writer.writeEmptyElement(textNS, QString::fromLatin1("p"));
        writer.writeAttribute(textNS, QString::fromLatin1("style-name"), QString::fromLatin1("p%1")
            .arg(block.blockFormatIndex()));
        if (block.textList())
            writer.writeEndElement(); // numbered-paragraph
        return;
    }
    writer.writeStartElement(textNS, QString::fromLatin1("p"));
    writer.writeAttribute(textNS, QString::fromLatin1("style-name"), QString::fromLatin1("p%1")
        .arg(block.blockFormatIndex()));
    for (QTextBlock::Iterator frag= block.begin(); !frag.atEnd(); frag++) {
        writer.writeCharacters(QString()); // Trick to make sure that the span gets no linefeed in front of it.
        writer.writeStartElement(textNS, QString::fromLatin1("span"));

        QString fragmentText = frag.fragment().text();
        if (fragmentText.length() == 1 && fragmentText[0] == 0xFFFC) { // its an inline character.
            writeInlineCharacter(writer, frag.fragment());
            writer.writeEndElement(); // span
            continue;
        }

        writer.writeAttribute(textNS, QString::fromLatin1("style-name"), QString::fromLatin1("c%1")
            .arg(frag.fragment().charFormatIndex()));
        bool escapeNextSpace = true;
        int precedingSpaces = 0;
        int exportedIndex = 0;
        for (int i=0; i <= fragmentText.count(); ++i) {
            bool isSpace = false;
                QChar character = fragmentText[i];
                isSpace = character.unicode() == ' ';

            // find more than one space. -> <text:s text:c="2" />
            if (!isSpace && escapeNextSpace && precedingSpaces > 1) {
                const bool startParag = exportedIndex == 0 && i == precedingSpaces;
                if (!startParag)
                    writer.writeCharacters(fragmentText.mid(exportedIndex, i - precedingSpaces + 1 - exportedIndex));
                writer.writeEmptyElement(textNS, QString::fromLatin1("s"));
                const int count = precedingSpaces - (startParag?0:1);
                if (count > 1)
                    writer.writeAttribute(textNS, QString::fromLatin1("c"), QString::number(count));
                precedingSpaces = 0;
                exportedIndex = i;
            }

            if (i < fragmentText.count()) {
                if (character.unicode() == 0x2028) { // soft-return
                    //if (exportedIndex < i)
                        writer.writeCharacters(fragmentText.mid(exportedIndex, i - exportedIndex));
                    writer.writeEmptyElement(textNS, QString::fromLatin1("line-break"));
                    exportedIndex = i+1;
                    continue;
                } else if (character.unicode() == '\t') { // Tab
                    //if (exportedIndex < i)
                        writer.writeCharacters(fragmentText.mid(exportedIndex, i - exportedIndex));
                    writer.writeEmptyElement(textNS, QString::fromLatin1("tab"));
                    exportedIndex = i+1;
                    precedingSpaces = 0;
                } else if (isSpace) {
                    ++precedingSpaces;
                    escapeNextSpace = true;
                } else if (!isSpace) {
                    precedingSpaces = 0;
                }
            }
        }

        writer.writeCharacters(fragmentText.mid(exportedIndex));
        writer.writeEndElement(); // span
    }
    writer.writeCharacters(QString()); // Trick to make sure that the span gets no linefeed behind it.
    writer.writeEndElement(); // p
    if (block.textList())
        writer.writeEndElement(); // list-item
}