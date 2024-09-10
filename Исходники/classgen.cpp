static void writeHeaderIncludes(const Class& classData, Class::Role role,
        QTextStream& stream)
{
    QMap<QString, Set> includes;
    Set forwards;

    QValueList<Method>::ConstIterator it    = classData.methods.begin();
    QValueList<Method>::ConstIterator endIt = classData.methods.end();
    for (; it != endIt; ++it)
    {
        if ((*it).arguments.isEmpty()) continue;

        extractHeaderIncludes(*it, includes);
        extractForwardDeclarations(*it, forwards);
    }

    it    = classData.msignals.begin();
    endIt = classData.msignals.end();
    for (; it != endIt; ++it)
    {
        if ((*it).arguments.isEmpty()) continue;

        extractHeaderIncludes(*it, includes);
        extractForwardDeclarations(*it, forwards);
    }


    QValueList<Property>::ConstIterator propertyIt = classData.properties.begin();
    QValueList<Property>::ConstIterator propertyEndIt = classData.properties.end();
    for (; propertyIt != propertyEndIt; ++propertyIt)
    {
        if (!(*propertyIt).headerIncludes.isEmpty())
        {
            QMap<QString, QStringList>::ConstIterator mapIt =
                (*propertyIt).headerIncludes.begin();
            QMap<QString, QStringList>::ConstIterator mapEndIt =
                (*propertyIt).headerIncludes.end();

            for (; mapIt != mapEndIt; ++mapIt)
            {
                includes[mapIt.key()].insertStringList(mapIt.data());
            }
        }

        if (!(*propertyIt).forwardDeclarations.isEmpty())
        {
            forwards.insertStringList((*propertyIt).forwardDeclarations);
        }
    }

    switch (role)
    {
        case Class::Interface:
            includes["qdbus"].insertString("<dbus/qdbusobject.h>");
            forwards.insertString("class QDBusError");
            forwards.insertString("class QDomElement");
            if (!classData.msignals.isEmpty())
                forwards.insertString("class QString");
            if (!classData.asyncMethods.isEmpty())
            {
                includes["Qt"].insertString("<qmap.h>");
                forwards.remove("template <typename K, typename V> class QMap");

                includes["qdbus"].insertString("<dbus/qdbusmessage.h>");
                forwards.remove("class QDBusMessage");
            }
            break;

        case Class::Proxy:
            includes["Qt"].insertString("<qobject.h>");
            forwards.insertString("class QDBusConnection");
            forwards.insertString("class QDBusError");
            forwards.insertString("class QDBusMessage");
            forwards.insertString("class QDBusProxy");
            forwards.insertString("class QString");
            if (!classData.properties.isEmpty())
                forwards.insertString("class QDBusVariant");
            if (!classData.asyncMethods.isEmpty())
            {
                includes["Qt"].insertString("<qmap.h>");
                forwards.remove("template <typename K, typename V> class QMap");
            }
            break;

        case Class::Node:
            includes["qdbus"].insertString("<dbus/qdbusobject.h>");
            forwards.insertString("class QDBusConnection");
            forwards.insertString("class QString");
            break;
    }

    if (!includes["Qt"].isEmpty())
        writeIncludes("Qt", includes["Qt"], stream);

    if (!includes["qdbus"].isEmpty())
        writeIncludes("Qt D-Bus", includes["qdbus"], stream);

    if (!includes["local"].isEmpty())
        writeIncludes("local", includes["local"], stream);

    stream << "// forward declarations" << endl;
    Set::ConstIterator setIt    = forwards.begin();
    Set::ConstIterator setEndIt = forwards.end();
    for (; setIt != setEndIt; ++setIt)
    {
        stream << setIt.key() << ";" << endl;
    }
    stream << endl;
}