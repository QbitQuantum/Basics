// Draws a timescale (physical). Note this can fail if the span is short
// enough which can happen when we find no events.
QString VisWidget::drawTimescale(QPainter * painter, unsigned long long start,
                              unsigned long long span, int margin)
{
    // Draw the scale bar
    int lineHeight = rect().height() - (timescaleHeight - 1);
    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine));
    painter->drawLine(margin, lineHeight, rect().width() - margin, lineHeight);

    if (!visProcessed)
        return "";

    painter->setFont(QFont("Helvetica", 10));
    QFontMetrics font_metrics = this->fontMetrics();

    // Figure out the units and number of ticks ( may handle units later )
    QLocale systemlocale = QLocale::system();
    QString text = systemlocale.toString(start);
    int textWidth = font_metrics.width(text) * 1.4;

    // We can't have more than this and fit text
    int max_ticks = floor((rect().width() - 2*margin) / 1.0 / textWidth);

    int y = lineHeight + timescaleTickHeight + font_metrics.xHeight() + 4;

    // We want a round number
    unsigned long long tick_span = span / max_ticks; // Not round
    int power = floor(log10(tick_span)); // How many zeros
    unsigned long long roundfactor = std::max(1.0, pow(10, power));
    tick_span = (tick_span / roundfactor) * roundfactor; // Now round
    if (tick_span < 1)
        tick_span = 1;

    // Now we must find the first number after startTime divisible by
    // the tick_span. We don't want to just find the same roundness
    // because then panning doesn't work.
    unsigned long long tick = (tick_span - start % tick_span) + start;

    // TODO: MAKE THIS PART OPTIONAL
    QString seconds = getUnits(trace->units);
    int tick_divisor = 1;
    unsigned long long tick_base = 0;
    if (!options->absoluteTime)
    {
        tick_base = tick - tick_span;
        int span_unit = (int) floor(log10(tick_span));
        tick_divisor = pow(3 * floor(span_unit / 3), 10);
        if (!tick_divisor)
            tick_divisor = 1;
        seconds = systemlocale.toString(tick_base
                                        / pow((double) trace->units, 10),
                                        'f', trace->units - span_unit)
                                        + "s + "
                                        + getUnits(trace->units
                                                   - 3 * floor(span_unit / 3))
                                        + ":";
    }


    // And now we draw
    while (tick < start + span)
    {
        int x = margin + round((tick - start) / 1.0 / span
                               * (rect().width() - 2*margin));
        painter->drawLine(x, lineHeight, x, lineHeight + timescaleTickHeight);
        text = systemlocale.toString((tick - tick_base) / tick_divisor);
        textWidth = font_metrics.width(text) / 3;
        painter->drawText(x - textWidth, y, text);

        tick += tick_span;
    }
    return seconds;
}