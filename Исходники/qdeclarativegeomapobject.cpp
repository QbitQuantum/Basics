// Currently item creation is tightly bound to landmark model. Some day
// this may be leveraged to any user defined model or e.g. XML model.
QDeclarativeGeoMapObject* QDeclarativeGeoMapObjectView::createItem(int modelRow)
{
    if (!delegate_ || !model_)
        return NULL;
    QModelIndex index = model_->index(modelRow, 0); // column 0
    if (!index.isValid()) {
        qWarning() << "QDeclarativeGeoMapObject Index is not valid: " << modelRow;
        return NULL;
    }
    QHashIterator<int, QByteArray> iterator(model_->roleNames());
    QDeclarativeContext *itemContext = new QDeclarativeContext(qmlContext(this));
    while (iterator.hasNext()) {
        iterator.next();
        QVariant modelData = model_->data(index, iterator.key());
        if (!modelData.isValid())
            continue;
        // This call would fail for <QObject*> Need to be figured out why
        // if the model support is leveraged.
        QObject *data_ptr = modelData.value<QDeclarativeLandmark*>();
        if (!data_ptr)
            continue;
        itemContext->setContextProperty(QLatin1String(iterator.value().data()), data_ptr);
        // To avoid name collisions (delegate has same named attribute as model's role)
        // one can add here that the data is accessible also e.g. via 'model'.
        // In case of landmarks, two of the following are then equivalent:
        // latitude : landmark.coordinate.latitude
        // latitude : model.landmark.coordinate.latitude
        // itemContext->setContextProperty(QLatin1String("model."), data_ptr);
        // At the time being, it is however uncertain how to make it from a
        // QtMobility project (QDeclarativeVisualDataModel not available).
        // This however needs to be figured out if model support is generalized.
    }
    QObject* obj = delegate_->create(itemContext);

    if (!obj) {
        qWarning() << "QDeclarativeGeoMapObject map object creation failed.";
        delete itemContext;
        return NULL;
    }
    QDeclarativeGeoMapObject *declMapObj =  qobject_cast<QDeclarativeGeoMapObject*>(obj);
    if (!declMapObj) {
        qWarning() << "QDeclarativeGeoMapObject map object delegate is of unsupported type.";
        delete itemContext;
        return NULL;
    }
    itemContext->setParent(declMapObj);
    return declMapObj;
}