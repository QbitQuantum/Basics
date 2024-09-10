bool QPushButtonPrivate::hitButton(const QPoint &pos)
{
    Q_Q(QPushButton);
    QRect roundedRect(q->rect().left() + QMacStylePrivate::PushButtonLeftOffset,
                      q->rect().top() + QMacStylePrivate::PushButtonContentPadding,
                      q->rect().width() - QMacStylePrivate::PushButtonRightOffset,
                      q->rect().height() - QMacStylePrivate::PushButtonBottomOffset);
    return roundedRect.contains(pos);
}