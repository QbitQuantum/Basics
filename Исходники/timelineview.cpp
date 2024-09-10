void TimelineView::updateTimeline(bool updateStartX)
{
    if (!m_delegate)
        return;

    if (!m_ranges.isArray())
        return;

    int length = m_ranges.property("length").toInt32();

    qreal startValue = m_ranges.property(0).property("start").toNumber();
    qreal endValue = m_ranges.property(length-1).property("start").toNumber() + m_ranges.property(length-1).property("duration").toNumber();

    qreal totalRange = endValue - startValue;
    qreal window = m_endTime - m_startTime;

    if (window == 0)    //###
        return;

    qreal spacing = width() / window;
    qreal oldtw = m_totalWidth;
    m_totalWidth = totalRange * spacing;

    // Find region samples
    int minsample = 0;
    int maxsample = 0;

    for (int i = 0; i < length; ++i) {
        if (m_ends.at(i) >= m_startTime)
            break;
        minsample = i;
    }

    for (int i = minsample + 1; i < length; ++i) {
        maxsample = i;
        if (m_starts.at(i) > m_endTime)
            break;
    }

    //### overkill (if we can expose whether or not data is nested)
    for (int i = maxsample + 1; i < length; ++i) {
        if (m_starts.at(i) < m_endTime)
            maxsample = i;
    }

    //qDebug() << maxsample - minsample;

    if (updateStartX) {
        qreal oldStartX = m_startX;
        m_startX = qRound(m_startTime * spacing);
        if (m_startX != oldStartX) {
            emit startXChanged(m_startX);
        }
    }

    //### emitting this before startXChanged was causing issues
    if (m_totalWidth != oldtw)
        emit totalWidthChanged(m_totalWidth);

    //clear items no longer in view
    while (prevMin < minsample) {
        delete m_items.take(prevMin);
        ++prevMin;
    }
    while (prevMax > maxsample) {
        delete m_items.take(prevMax);
        --prevMax;
    }

    // Show items
    int z = 0;
    for (int i = maxsample-1; i >= minsample; --i) {
        QDeclarativeItem *item = 0;
        item = m_items.value(i);
        bool creating = false;
        if (!item) {
            QDeclarativeContext *ctxt = new QDeclarativeContext(qmlContext(this));
            item = qobject_cast<QDeclarativeItem*>(m_delegate->beginCreate(ctxt));
            m_items.insert(i, item);
            creating = true;

            int type = m_ranges.property(i).property("type").toNumber();

            ctxt->setParent(item); //### QDeclarative_setParent_noEvent(ctxt, item); instead?
            ctxt->setContextProperty("duration", qMax(qRound(m_ranges.property(i).property("duration").toNumber()/qreal(1000)),1));
            ctxt->setContextProperty("fileName", m_ranges.property(i).property("fileName").toString());
            ctxt->setContextProperty("line", m_ranges.property(i).property("line").toNumber());
            QString label;
            QVariantList list = m_ranges.property(i).property("label").toVariant().value<QVariantList>();
            for (int i = 0; i < list.size(); ++i) {
                if (i > 0)
                    label += QLatin1Char('\n');
                QString sub = list.at(i).toString();

                //### only do rewrite for bindings...
                if (type == 3) {
                    //### don't construct in loop
                    QRegExp rewrite("\\(function \\$(\\w+)\\(\\) \\{ return (.+) \\}\\)");
                    bool match = rewrite.exactMatch(sub);
                    if (match)
                        sub = rewrite.cap(1) + ": " + rewrite.cap(2);
                }

                label += sub;
            }
            ctxt->setContextProperty("label", label);
            ctxt->setContextProperty("type", type);
            item->setParentItem(this);
        }
        if (item) {
            item->setX(m_starts.at(i)*spacing);
            item->setWidth((m_ends.at(i)-m_starts.at(i)) * spacing);
            item->setZValue(++z);
        }
        if (creating)
            m_delegate->completeCreate();
    }

    prevMin = minsample;
    prevMax = maxsample;
}