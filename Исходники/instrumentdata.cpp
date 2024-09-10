/*
 * Removes bad characters
 */
QString InstrumentData::cleanWord(QString data)
{
    QString out;
    QChar c;

    for(auto i = data.begin(); i != data.end(); ++i){
        c = *i;
        if(c.isLetterOrNumber()||c.isPunct()) out.append(c);
    }

    return out;
}