QString TextUtils::sanitize(QString const& original)
{
    QString result;

    for (int i = 0; i < original.length(); i++)
    {
        QChar c = original.at(i);
        uchar_t mychar = c.toAscii();
        bool valid = sfn_chars[mychar/8] & ( 1 << (mychar % 8) );

        if (valid) {
            result.append(c);
        } else {
            result.append("_");
        }
    }

    return result;
}