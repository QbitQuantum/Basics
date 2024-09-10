void  ModelContact::editContact(const QVector<QString>& param)
{
    if (param.size() < 4)
        throw new Exception("Error: missing parameters to edit contact");
    const QString& name = param[0];
    const QString& key  = param[1];
    const QString& ip   = param[2];
    const QString& old  = param[3];

    QVector<QString> v;
    v.append(old);
    this->delContact(v);
    v.remove(0);
    v.append(name);
    v.append(key);
    v.append(ip);
    //this->addContact(v);
}