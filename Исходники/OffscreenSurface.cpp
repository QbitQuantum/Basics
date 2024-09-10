void OffscreenSurface::finishQmlLoad(QQmlComponent* qmlComponent,
                                     QQmlContext* qmlContext,
                                     QQuickItem* parent,
                                     const QmlContextObjectCallback& callback) {
    disconnect(qmlComponent, &QQmlComponent::statusChanged, this, 0);
    if (qmlComponent->isError()) {
        for (const auto& error : qmlComponent->errors()) {
            qCWarning(qmlLogging) << error.url() << error.line() << error;
        }
        qmlComponent->deleteLater();
        return;
    }

    QObject* newObject = qmlComponent->beginCreate(qmlContext);
    if (qmlComponent->isError()) {
        for (const auto& error : qmlComponent->errors()) {
            qCWarning(qmlLogging) << error.url() << error.line() << error;
        }
        if (!getRootItem()) {
            qFatal("Unable to finish loading QML root");
        }
        qmlComponent->deleteLater();
        return;
    }

    if (!newObject) {
        if (!getRootItem()) {
            qFatal("Could not load object as root item");
            return;
        }
        qCWarning(qmlLogging) << "Unable to load QML item";
        return;
    }

    qmlContext->engine()->setObjectOwnership(this, QQmlEngine::CppOwnership);

    // All quick items should be focusable
    QQuickItem* newItem = qobject_cast<QQuickItem*>(newObject);
    if (newItem) {
        // Make sure we make items focusable (critical for
        // supporting keyboard shortcuts)
        newItem->setFlag(QQuickItem::ItemIsFocusScope, true);
#ifdef DEBUG
        for (auto frame : newObject->findChildren<QQuickItem *>("Frame")) {
            frame->setProperty("qmlFile", qmlComponent->url());
        }
#endif
    }

    bool rootCreated = getRootItem() != nullptr;

    // Make sure we will call callback for this codepath
    // Call this before qmlComponent->completeCreate() otherwise ghost window appears
    // If we already have a root, just set a couple of flags and the ancestry
    if (rootCreated) {
        callback(qmlContext, newItem);
        if (!parent) {
            parent = getRootItem();
        }
        // Allow child windows to be destroyed from JS
        QQmlEngine::setObjectOwnership(newObject, QQmlEngine::JavaScriptOwnership);
        newObject->setParent(parent);
        newItem->setParentItem(parent);
    } else {
        // The root item is ready. Associate it with the window.
        _sharedObject->setRootItem(newItem);
    }

    qmlComponent->completeCreate();
    qmlComponent->deleteLater();

    onItemCreated(qmlContext, newItem);

    if (!rootCreated) {
        connect(newItem, SIGNAL(sendToScript(QVariant)), this, SIGNAL(fromQml(QVariant)));
        onRootCreated();
        emit rootItemCreated(newItem);
        // Call this callback after rootitem is set, otherwise VrMenu wont work
        callback(qmlContext, newItem);
    }
}