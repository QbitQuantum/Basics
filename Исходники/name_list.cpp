void NameList::addChildToTree(QString parentName, QString childName, int index) {
    bool childExists = root->findChild<QObject*>(childName) != 0;
    if (!childExists) {
        QObject *child = new QObject;
        child->setObjectName(childName);
        child->setProperty("index", index);
        QObject *parent = parentName.isEmpty() ? root : root->findChild<QObject*>(parentName);
        Q_ASSERT(parent);
        child->setParent(parent);
    }
}