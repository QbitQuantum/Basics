QRect SparqlTextEdit::lineNumbersRect() const
{
    QRect frame = frameRect();
    frame.adjust(frameWidth(), frameWidth(), -frameWidth(), -frameWidth());
    frame.setWidth(qMin(frame.width(), leftMargin));
    return frame;
}