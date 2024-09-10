QMetaObject *metaObjectFor(GoTypeInfo *typeInfo)
{
    if (typeInfo->metaObject) {
            return reinterpret_cast<QMetaObject *>(typeInfo->metaObject);
    }

    QMetaObjectBuilder mob;
    if (typeInfo->paint) {
        mob.setSuperClass(&QQuickPaintedItem::staticMetaObject);
    } else {
        mob.setSuperClass(&QObject::staticMetaObject);
    }
    mob.setClassName(typeInfo->typeName);
    mob.setFlags(QMetaObjectBuilder::DynamicMetaObject);

    GoMemberInfo *memberInfo;
    
    memberInfo = typeInfo->fields;
    int relativePropIndex = mob.propertyCount();
    for (int i = 0; i < typeInfo->fieldsLen; i++) {
        mob.addSignal("__" + QByteArray::number(relativePropIndex) + "()");
        const char *typeName = "QVariant";
        if (memberInfo->memberType == DTListProperty) {
            typeName = "QQmlListProperty<QObject>";
        }
        QMetaPropertyBuilder propb = mob.addProperty(memberInfo->memberName, typeName, relativePropIndex);
        propb.setWritable(true);
        memberInfo->metaIndex = relativePropIndex;
        memberInfo++;
        relativePropIndex++;
    }

    memberInfo = typeInfo->methods;
    int relativeMethodIndex = mob.methodCount();
    for (int i = 0; i < typeInfo->methodsLen; i++) {
        if (*memberInfo->resultSignature) {
            mob.addMethod(memberInfo->methodSignature, memberInfo->resultSignature);
        } else {
            mob.addMethod(memberInfo->methodSignature);
        }
        memberInfo->metaIndex = relativeMethodIndex;
        memberInfo++;
        relativeMethodIndex++;
    }

    // TODO Support default properties.
    //mob.addClassInfo("DefaultProperty", "objects");

    QMetaObject *mo = mob.toMetaObject();

    // Turn the relative indexes into absolute indexes.
    memberInfo = typeInfo->fields;
    int propOffset = mo->propertyOffset();
    for (int i = 0; i < typeInfo->fieldsLen; i++) {
        memberInfo->metaIndex += propOffset;
        memberInfo++;
    }
    memberInfo = typeInfo->methods;
    int methodOffset = mo->methodOffset();
    for (int i = 0; i < typeInfo->methodsLen; i++) {
        memberInfo->metaIndex += methodOffset;
        memberInfo++;
    }

    typeInfo->metaObject = mo;
    return mo;
}