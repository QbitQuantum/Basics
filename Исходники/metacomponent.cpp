// Component type is the one passed inside QML (registered name)
MetaComponent * MetaComponent::create(const QString &componentType, QObject *parent)
{
    // 1. Try to get the C++ metatype registered from the QML name
    // Right now, we run through all registered QML modules, and get the correct one.
    // If several are found, we break. Not the nicest, but we can do something better later.
    QList<QQmlType *> types = QQmlMetaType::qmlTypes();
    QList<QByteArray> found;
    foreach (const QQmlType *type, types) {
        if (type->elementName() == componentType) {
            found.append(type->typeName());
        }
    }

    if (found.isEmpty()) {
        qWarning() << "No QML component were registered with name" << componentType;
        return 0;
    }

    if (found.count() > 1) {
        qWarning() << "Several QML components were registered with name" << componentType;
        return 0;
    }

    QByteArray cppTypeByteArray = found.first();
    cppTypeByteArray.append("*");
    const char *cppType = QMetaObject::normalizedType(cppTypeByteArray).constData();


    // 2. Try to get the Phonebot MetaData
    int componentTypeIndex = QMetaType::type(cppType);
    if (componentTypeIndex == QMetaType::UnknownType) {
        qWarning() << "Cannot get Phonebot metadata from" << componentType << ":"
                   << "Cannot find Qt metatype for" << cppType
                   << "It might not be registered via qmlRegisterType.";
        return 0;
    }

    const QMetaObject *componentMeta = QMetaType::metaObjectForType(componentTypeIndex);
    int metaClassInfoIndex = componentMeta->indexOfClassInfo("meta");
    if (metaClassInfoIndex == -1) {
        qWarning() << "Cannot get Phonebot metadata from" << componentType << ":"
                   << cppType << "don't have a Phonebot metatype."
                   << "Did you forgot PHONEBOT_METADATA macro ?";
        return 0;
    }

    QMetaClassInfo metaClassInfo = componentMeta->classInfo(metaClassInfoIndex);
    QByteArray metaNameByteArray (metaClassInfo.value());
    metaNameByteArray.append("*");
    const char *metaName = QMetaObject::normalizedType(metaNameByteArray).constData();

    int metaTypeIndex = QMetaType::type(metaName);
    if (metaTypeIndex == QMetaType::UnknownType) {
        qWarning() << "Cannot get Phonebot metadata from" << componentType << ":"
                   << "Cannot find Qt metatype for Phonebot metatype" << metaName
                   << "It might not be registered via qDeclareMetaType.";
        return 0;
    }

    // Check if it inherits from AbstractMetaData
    bool ok = false;
    const QMetaObject *componentMetaMeta = QMetaType::metaObjectForType(metaTypeIndex);
    const QMetaObject *super = componentMetaMeta;
    while (super) {
        if (!ok) {
            ok =  (super->className() == AbstractMetaData::staticMetaObject.className());
        }
        super = super->superClass();
    }

    if (!ok) {
        qWarning() << "Cannot get Phonebot metadata from" << componentType << ":"
                   << "Phonebot metatype class" << metaName << "don't inherit from"
                   << AbstractMetaData::staticMetaObject.className();
        return 0;
    }

    // Construct
    QObject *meta = componentMetaMeta->newInstance();
    if (!meta) {
        qWarning() << "Cannot get Phonebot metadata from" << componentType << ":"
                   << "Phonebot metatype class " << metaName
                   << "don't have an invokable constructor and cannot be created.";
        return 0;
    }
    AbstractMetaData *castedMeta = qobject_cast<AbstractMetaData *>(meta);
    Q_ASSERT(castedMeta);

    QSet<QString> properties;
    for (int i = componentMeta->propertyOffset(); i < componentMeta->propertyCount(); ++i) {
        properties.insert(componentMeta->property(i).name());
    }

    QStringList removedProperties;
    foreach (const QString &property, properties) {
        if (!castedMeta->property(property)) {
            qWarning() << property << "do not have metadata registered";
        }
    }

    foreach (const QString &property, removedProperties) {
        properties.remove(property);
    }