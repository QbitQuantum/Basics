void StyledLabel::updateToolTip()
{
    if (frameRect().width() - 2*frameWidth() < _layout.minimumWidth())
        setToolTip(QString("<qt>%1</qt>").arg(Qt::escape(_layout.text())));  // only rich text gets wordwrapped!
    else
        setToolTip(QString());
}