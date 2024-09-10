bool QNickValidator::isBegEndChar(QChar ch) const
{
    return ch.isLetterOrNumber() || ch.isPunct();
}