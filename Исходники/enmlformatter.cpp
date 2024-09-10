QByteArray EnmlFormatter::fixEncryptionTags(QByteArray newContent) {
    int endPos, startPos, endData,slotStart, slotEnd;
    QByteArray eTag = "<table class=\"en-crypt-temp\"";
    for (int i=newContent.indexOf(eTag); i>0; i = newContent.indexOf(eTag,i+1)) {
        slotStart = newContent.indexOf("slot", i+1)+6;
        slotEnd = newContent.indexOf("\"",slotStart+1);
        QString slot = newContent.mid(slotStart, slotEnd-slotStart);
        slot = slot.replace("\"", "");
        startPos = newContent.indexOf("<td>", i+1)+4;
        endData = newContent.indexOf("</td>",startPos);
        QString text = newContent.mid(startPos,endData-startPos);
        endPos = newContent.indexOf("</table>",i+1)+8;

        // Encrypt the text
        QPair<QString, QString> pair = global.passwordSafe.value(slot);
        QString password = pair.first;
        QString hint = pair.second;
        EnCrypt crypt;
        QString encrypted;
        crypt.encrypt(encrypted, text, password);

        // replace the table with an en-crypt tag.
        QByteArray start = newContent.mid(0,i-1);
        QByteArray end = newContent.mid(endPos);
        newContent.clear();
        newContent.append(start);
        newContent.append(QByteArray("<en-crypt cipher=\"RC2\" length=\"64\" hint=\""));
        newContent.append(hint.toLocal8Bit());
        newContent.append(QByteArray("\">"));
        newContent.append(encrypted.toLocal8Bit());
        newContent.append(QByteArray("</en-crypt>"));
        newContent.append(end);
    }
    return newContent;
}