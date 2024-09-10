void QScintillaWidget::changeEvent(QEvent *pEvent)
{
    // Default handling of the event

    QsciScintilla::changeEvent(pEvent);

    // Check whether the palette has changed and if so then update our colors

    if (pEvent->type() == QEvent::PaletteChange)
        updateColors();
}