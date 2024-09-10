void Filer::generateName(bool aSmgExt)
{
    QString s = patchedFileName;
    if (aSmgExt) {
        s.remove(".smg");
    }
    int endString = s.size() - 1;

    QChar ch = patchedFileName.at(endString);
    if (!(ch.isDigit())) {
        patchedFileName = s + QString::number(generateNum(s, 0, aSmgExt));
    } else {
        QString num;
        int i;
        for (i = endString; i >= 0; --i) {
            if (s.at(i).isDigit()) {
                num.insert(0, s.at(i));
            } else {
                break;
            }
        }
        s = s.left(i + 1);
        patchedFileName = s + QString::number(generateNum(s, num.toInt(), aSmgExt));
}

    if (aSmgExt) {
        patchedFileName += ".smg";
    }
}