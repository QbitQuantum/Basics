void ZoomableAssemblyOverview::drawCoordLabels(QPainter & p) {
    const static int xoffset = 4;
    const static int yoffset = 3;

    U2OpStatusImpl status;

    //Prepare text
    QString visibleStartText = QString::number(visibleRange.startPos);
    QString visibleEndText = QString::number(visibleRange.endPos());
    QString visibleDiffText = QString::number(visibleRange.length);
    insertSpaceSeparators(visibleStartText);
    insertSpaceSeparators(visibleEndText);
    insertSpaceSeparators(visibleDiffText);

    //Prepare font
    QFont font = p.font();
#if QT_VERSION >= QT_VERSION_CHECK(4, 7, 0)
        font.setStyleHint(QFont::SansSerif, (QFont::StyleStrategy)(QFont::PreferAntialias | QFont::ForceIntegerMetrics));
#else
        font.setStyleHint(QFont::SansSerif, QFont::PreferAntialias);
#endif
    p.setFont(font);
    QFontMetrics fontMetrics(font, this);

    p.setPen(labelForegroundColor);

    //draw Visible Region
    QString visibleRegionText = tr("%1 to %2 (%3 bp)").arg(visibleStartText).arg(visibleEndText).arg(visibleDiffText);
    QRect grtRect = QRect(0, 0, fontMetrics.width(visibleRegionText), fontMetrics.height());
    grtRect.translate(xoffset, rect().height() - yoffset - grtRect.height());
    if(rect().contains(grtRect)) {
        p.fillRect(grtRect, labelBackgroundColor);
        p.drawText(grtRect, visibleRegionText);
    }

    //draw Selected Region
    qint64 from = browser->getXOffsetInAssembly();
    qint64 to = qMin(browser->getXOffsetInAssembly() + browser->basesCanBeVisible(), model->getModelLength(status));

    //prepare text
    QString fromText = QString::number(from + 1); // because of 1-based coords
    QString toText = QString::number(to);
    QString diff = QString::number(to - from);

    insertSpaceSeparators(fromText);
    insertSpaceSeparators(toText);
    insertSpaceSeparators(diff);

    //draw text
    QString selectedRegionText = tr("%1 to %2 (%3 bp)").arg(fromText, toText, diff);
    QRect srtRect = QRect(0, 0, fontMetrics.width(selectedRegionText), fontMetrics.height());
    srtRect.translate(rect().width() - srtRect.width() - xoffset, rect().height() - yoffset - grtRect.height());
    if(rect().contains(srtRect) && !srtRect.intersects(grtRect)) {
        p.fillRect(srtRect, labelBackgroundColor);
        p.drawText(srtRect, selectedRegionText);
    }
}