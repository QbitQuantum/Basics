int KReportItemField::renderSimpleData(OROPage *page, OROSection *section, const QPointF &offset,
                                        const QVariant &data, KReportScriptHandler *script)
{
    OROTextBox * tb = new OROTextBox();
    tb->setPosition(scenePosition(position()) + offset);
    tb->setSize(sceneSize(size()));
    tb->setFont(font());
    tb->setFlags(textFlags());
    tb->setTextStyle(textStyle());
    tb->setLineStyle(lineStyle());
    tb->setCanGrow(m_canGrow->value().toBool());
    tb->setWordWrap(m_wordWrap->value().toBool());

    QString str;

    QString ids = itemDataSource();
    if (!ids.isEmpty()) {
#ifdef KREPORT_SCRIPTING
        if (ids.left(1) == QLatin1String("=") && script) { //Everything after = is treated as code
            if (!ids.contains(QLatin1String("PageTotal()"))) {
                QVariant v = script->evaluate(ids.mid(1));
                str = v.toString();
            } else {
                str = ids.mid(1);
                tb->setRequiresPostProcessing(true);
            }
        } else
#else
        Q_UNUSED(script);
#endif
        if (ids.left(1) == QLatin1String("$")) { //Everything past $ is treated as a string
            str = ids.mid(1);
        } else {
            str = data.toString();
        }
    } else {
            str = m_itemValue->value().toString();
    }

    tb->setText(str);

    //Work out the size of the text
    if (tb->canGrow()) {
        QRect r;
        if (tb->wordWrap()) {
            //Grow vertically
            QFontMetrics metrics(font());
            QRect temp(tb->position().x(), tb->position().y(), tb->size().width(), 5000); // a large vertical height
            r = metrics.boundingRect(temp, tb->flags(), str);
        } else {
            //Grow Horizontally
            QFontMetrics metrics(font());
            QRect temp(tb->position().x(), tb->position().y(), 5000, tb->size().height()); // a large vertical height
            r = metrics.boundingRect(temp, tb->flags(), str);
        }
        tb->setSize(r.size() + QSize(4,4));
    }

    if (page) {
        page->insertPrimitive(tb);
    }

    if (section) {
        OROPrimitive *clone = tb->clone();
        clone->setPosition(scenePosition(position()));
        section->addPrimitive(clone);
    }
    int height = scenePosition(position()).y() + tb->size().height();
    //If there is no page to add the item to, delete it now because it wont be deleted later
    if (!page) {
        delete tb;
    }
    return height;
}