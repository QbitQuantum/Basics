QDeclarativePackage::~QDeclarativePackage()
{
    Q_D(QDeclarativePackage);
    for (int ii = 0; ii < d->dataList.count(); ++ii) {
        QObject *obj = d->dataList.at(ii);
        obj->setParent(this);
    }
}