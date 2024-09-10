void CiscoSecret7::transform(const QByteArray &input, QByteArray &output)
{
    if (wayValue == INBOUND) {
        QByteArray data;

        cipher(seed,input, data);
        output = data.toHex().prepend(QByteArray::number(seed));

    } else {
        QByteArray encrypted = input.toUpper();

        if (encrypted.isEmpty())
            return;

        if (encrypted.size() < 3) {
            emit error(tr("Invalid hash (far too small)"),id);
            return;
        }
        bool k = true;
        seed = encrypted.mid(0,2).toInt(&k);
        if (!k || seed > MAXSEED) {
            emit error(tr("Invalid seed, it must be an unsigned integer <= %1").arg(MAXSEED),id);
            return;
        }

        QByteArray data = encrypted.mid(2);
        data = fromHex(data);
        cipher(seed,data,output);
    }
}