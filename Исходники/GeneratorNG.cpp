QList<TLType> GeneratorNG::solveTypes(QMap<QString, TLType> types)
{
    QList<TLType> solvedTypes;
    QStringList solvedTypesNames = nativeTypes;
    solvedTypesNames.append(tlValueName);

    int previousSolvedTypesCount = -1;

    // In order to successful compilation, type must rely only on defined types.
    while (solvedTypes.count() != previousSolvedTypesCount) { // Check for infinity loop
        previousSolvedTypesCount = solvedTypes.count();
        foreach(const QString &typeName, types.keys()) {
            const TLType &type = types.value(typeName);

            bool solved = true;

            if (nativeTypes.contains(type.name)) {
                types.remove(typeName);
                continue;
            }

            foreach (const TLSubType &subType, type.subTypes) {
                foreach (const TLParam &member, subType.members) {
                    QString memberType = getTypeOrVectorType(member.type);

                    if (!solvedTypesNames.contains(memberType)) {
                        solved = false;
                        break;
                    }
                }

                if (!solved) {
                    break;
                }
            }

            if (solved) {
                solvedTypes.append(type);
                types.remove(typeName);
                solvedTypesNames.append(typeName);

                qDebug() << "Solved:" << typeName;
            }
        }
    }

    qDebug() << "Unresolved:" << types.count();

    return solvedTypes;
}