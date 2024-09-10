QObject *FlameGraph::appendChild(QObject *parentObject, QQuickItem *parentItem,
                                 QQmlContext *context, const QModelIndex &childIndex,
                                 qreal position, qreal size)
{
    QObject *childObject = m_delegate->beginCreate(context);
    if (parentItem) {
        QQuickItem *childItem = qobject_cast<QQuickItem *>(childObject);
        if (childItem)
            childItem->setParentItem(parentItem);
    }
    childObject->setParent(parentObject);
    FlameGraphAttached *attached = FlameGraph::qmlAttachedProperties(childObject);
    attached->setRelativePosition(position);
    attached->setRelativeSize(size);
    attached->setModelIndex(childIndex);
    m_delegate->completeCreate();
    return childObject;
}