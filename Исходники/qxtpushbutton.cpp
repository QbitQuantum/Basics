/*!
    \reimp
 */
QSize QxtPushButton::sizeHint() const
{
    QSize size;
    if (qxt_d().isRichText())
        size = qxt_d().doc->documentLayout()->documentSize().toSize();
    else
        size = QPushButton::sizeHint();

    if (qxt_d().rot & Vertical_Mask)
        size.transpose();
    return size;
}