void QDBusMetaObjectGenerator::parseMethods()
{
    //
    // TODO:
    //  Add cloned methods when the remote object has return types
    //

    QDBusIntrospection::Methods::ConstIterator method_it = data->methods.constBegin();
    QDBusIntrospection::Methods::ConstIterator method_end = data->methods.constEnd();
    for ( ; method_it != method_end; ++method_it) {
        const QDBusIntrospection::Method &m = *method_it;
        Method mm;

        mm.name = m.name.toLatin1();
        QByteArray prototype = mm.name;
        prototype += '(';

        bool ok = true;

        // build the input argument list
        for (int i = 0; i < m.inputArgs.count(); ++i) {
            const QDBusIntrospection::Argument &arg = m.inputArgs.at(i);

            Type type = findType(arg.type.toLatin1(), m.annotations, "In", i);
            if (type.id == QVariant::Invalid) {
                ok = false;
                break;
            }

            mm.inputSignature += arg.type.toLatin1();
            mm.inputTypes.append(type.id);

            mm.parameters.append(arg.name.toLatin1());
            mm.parameters.append(',');
            
            prototype.append(type.name);
            prototype.append(',');
        }
        if (!ok) continue;

        // build the output argument list:
        for (int i = 0; i < m.outputArgs.count(); ++i) {
            const QDBusIntrospection::Argument &arg = m.outputArgs.at(i);

            Type type = findType(arg.type.toLatin1(), m.annotations, "Out", i);
            if (type.id == QVariant::Invalid) {
                ok = false;
                break;
            }

            mm.outputSignature += arg.type.toLatin1();
            mm.outputTypes.append(type.id);

            if (i == 0) {
                // return value
                mm.typeName = type.name;
            } else {
                // non-const ref parameter
                mm.parameters.append(arg.name.toLatin1());
                mm.parameters.append(',');

                prototype.append(type.name);
                prototype.append("&,");
            }
        }
        if (!ok) continue;

        // convert the last commas:
        if (!mm.parameters.isEmpty()) {
            mm.parameters.truncate(mm.parameters.length() - 1);
            prototype[prototype.length() - 1] = ')';
        } else {
            prototype.append(')');
        }

        // check the async tag
        if (m.annotations.value(QLatin1String(ANNOTATION_NO_WAIT)) == QLatin1String("true"))
            mm.tag = "Q_NOREPLY";

        // meta method flags
        mm.flags = AccessPublic | MethodSlot | MethodScriptable;

        // add
        methods.insert(QMetaObject::normalizedSignature(prototype), mm);
    }
}