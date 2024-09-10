QList<const UserBaseInformations*> FreeUser::Search(QMap<QString,AUser*>::const_iterator begin,QMap<QString,AUser*>::const_iterator end, const UserBaseInformations &inf) const
{
    QSet<const UserBaseInformations*> nameSet;
    QSet<const UserBaseInformations*> emailSet;
    QSet<const UserBaseInformations*> resultSet;
    bool set = false;

    if(inf.GetName() != "")
    {

        for(QMap<QString,AUser*>::const_iterator it = begin;it != end ;it++)
        {
            if((*it)->Profile->GetName() == inf.GetName())
                nameSet.insert((*it)->Profile);
        }

        if(!set)
        {
            set = true;
            resultSet = nameSet;
        }
    }

    if(inf.GetEmail() != "")
    {
        for(QMap<QString,AUser*>::const_iterator it = begin;it != end ;it++)
        {
            if((*it)->Profile->GetEmail() == inf.GetEmail())
                emailSet.insert((*it)->Profile);
        }

        if(!set)
        {
            set = true;
            resultSet = emailSet;
        }
    }

    if(inf.GetName()!="")
        resultSet.intersect(nameSet);
    if(inf.GetEmail()!= "")
        resultSet.intersect(emailSet);

    //rimuovo se presente me stesso
    resultSet.remove(this->Profile);
    return QList<const UserBaseInformations*>::fromSet(resultSet);
}