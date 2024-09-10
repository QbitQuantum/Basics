void UmlOperation::java(QHash<QByteArray, QByteArray*> & prop)
{
    QByteArray d = JavaSettings::operationDef();
    QByteArray * v;

    if ((v = prop.value("Java/Final")) != 0) {
        if (*v == "TRUE")
            set_isJavaFinal(TRUE);

        prop.remove("Java/Final");
    }

    if ((v = prop.value("Java/Synchronized")) != 0) {
        if (*v == "TRUE")
            set_isJavaSynchronized(TRUE);

        prop.remove("Java/Synchronized");
    }

    if ((v = prop.value("Java/Static")) != 0) {
        if (*v == "TRUE")
            set_isClassMember(TRUE);

        prop.remove("Java/Static");
    }

    if ((v = prop.value("Java/Abstract")) != 0) {
        if (*v == "TRUE")
            set_isAbstract(TRUE);

        prop.remove("Java/Abstract");
    }

    if ((v = prop.value("Java/Strictfp")) != 0) {
        if (*v == "TRUE") {
            int index = d.indexOf("${final}");

            if (index != -1)
                d.insert(index, "strictfp ");
        }

        prop.remove("Java/Strictfp");
    }

    set_JavaDef(d);
}