int KReportItemText::renderSimpleData(OROPage *page, OROSection *section, const QPointF &offset,
                                       const QVariant &data, KReportScriptHandler *script)

{
    Q_UNUSED(script);

    QString qstrValue;

    QString cs = itemDataSource();

    if (!cs.isEmpty()) {
        if (cs.left(1) == QLatin1String("$")) { //Everything past $ is treated as a string
            qstrValue = cs.mid(1);
        } else {
            qstrValue = data.toString();
        }
    } else {
        qstrValue = m_itemValue->value().toString();
    }

    QPointF pos = m_pos.toScene();
    QSizeF size = m_size.toScene();
    pos += offset;

    QRectF trf(pos, size);
    qreal intStretch = trf.top() - offset.y();

    if (qstrValue.length()) {
        QRectF rect = trf;

        int pos = 0;
        QChar separator;
        QRegExp re(QLatin1String("\\s"));
        QPrinter prnt(QPrinter::HighResolution);
        QFontMetrics fm(font(), &prnt);

        // int   intRectWidth    = (int)(trf.width() * prnt.resolution()) - 10;
        int     intRectWidth    = (int)((m_size.toPoint().width() / 72) * prnt.resolution());
        int     intLineCounter  = 0;
        qreal   intBaseTop      = trf.top();
        qreal   intRectHeight   = trf.height();

        while (qstrValue.length()) {
            int idx = re.indexIn(qstrValue, pos);
            if (idx == -1) {
                idx = qstrValue.length();
                separator = QLatin1Char('\n');
            } else
                separator = qstrValue.at(idx);

            if (fm.boundingRect(qstrValue.left(idx)).width() < intRectWidth || pos == 0) {
                pos = idx + 1;
                if (separator == QLatin1Char('\n')) {
                    QString line = qstrValue.left(idx);

                    qstrValue.remove(0, idx + 1);

                    pos = 0;

                    rect.setTop(intBaseTop + (intLineCounter * intRectHeight));
                    rect.setBottom(rect.top() + intRectHeight);

                    OROTextBox * tb = new OROTextBox();
                    tb->setPosition(rect.topLeft());
                    tb->setSize(rect.size());
                    tb->setFont(font());
                    tb->setText(line);
                    tb->setFlags(textFlags());
                    tb->setTextStyle(textStyle());
                    tb->setLineStyle(lineStyle());

                    if (page) {
                        page->addPrimitive(tb);
                    }

                    if (section) {
                        OROTextBox *tb2 = dynamic_cast<OROTextBox*>(tb->clone());
                        tb2->setPosition(m_pos.toPoint());
                        section->addPrimitive(tb2);
                    }

                    if (!page) {
                        delete tb;
                    }

                    intStretch += intRectHeight;
                    intLineCounter++;
                }
            } else {
                QString line = qstrValue.left(pos - 1);
                qstrValue.remove(0, pos);
                pos = 0;

                rect.setTop(intBaseTop + (intLineCounter * intRectHeight));
                rect.setBottom(rect.top() + intRectHeight);

                OROTextBox * tb = new OROTextBox();
                tb->setPosition(rect.topLeft());
                tb->setSize(rect.size());
                tb->setFont(font());
                tb->setText(line);
                tb->setFlags(textFlags());
                tb->setTextStyle(textStyle());
                tb->setLineStyle(lineStyle());
                if (page) page->addPrimitive(tb);

                intStretch += intRectHeight;
                intLineCounter++;
            }
        }

        intStretch += (m_bottomPadding / 100.0);
    }

    return intStretch; //Item returns its required section height
}