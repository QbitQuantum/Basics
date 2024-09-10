QT_BEGIN_NAMESPACE

QQuickItem *QQuickTextUtil::createCursor(
    QQmlComponent *component, QQuickItem *parent, const QRectF &rectangle, const char *className)
{
    QQuickItem *item = 0;
    if (component->isReady()) {
        QQmlContext *creationContext = component->creationContext();

        if (QObject *object = component->beginCreate(creationContext
                              ? creationContext
                              : qmlContext(parent))) {
            if ((item = qobject_cast<QQuickItem *>(object))) {
                QQml_setParent_noEvent(item, parent);
                item->setParentItem(parent);
                item->setPosition(rectangle.topLeft());
                item->setHeight(rectangle.height());
            } else {
                qmlInfo(parent) << tr("%1 does not support loading non-visual cursor delegates.")
                                .arg(QString::fromUtf8(className));
            }
            component->completeCreate();
            return item;
        }
    } else if (component->isLoading()) {
        QObject::connect(component, SIGNAL(statusChanged(QQmlComponent::Status)),
                         parent, SLOT(createCursor()), Qt::UniqueConnection);
        return item;
    }
    qmlInfo(parent, component->errors()) << tr("Could not load cursor delegate");
    return item;
}