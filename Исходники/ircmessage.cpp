/*!
    \property bool IrcPrivateMessage::request
    This property is \c true if the message is a request; otherwise \c false.

    \par Access functions:
    \li bool <b>isRequest</b>() const
 */
bool IrcPrivateMessage::isRequest() const
{
    Q_D(const IrcMessage);
    QByteArray msg = d->parser.params().value(1);
    if (d->flags & (Identified | Unidentified))
        msg.remove(0, 1);
    return msg.startsWith('\1') && msg.endsWith('\1') && !isAction();
}