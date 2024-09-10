bool KNGroupListData::writeOut()
{
    QFile f(path + "groups");
    QCString temp;

    if(f.open(IO_WriteOnly))
    {
        for(KNGroupInfo *i = groups->first(); i; i = groups->next())
        {
            temp = i->name.utf8();
            switch(i->status)
            {
                case KNGroup::unknown:
                    temp += " u ";
                    break;
                case KNGroup::readOnly:
                    temp += " n ";
                    break;
                case KNGroup::postingAllowed:
                    temp += " y ";
                    break;
                case KNGroup::moderated:
                    temp += " m ";
                    break;
            }
            temp += i->description.utf8() + "\n";
            f.writeBlock(temp.data(), temp.length());
        }
        f.close();
        return true;
    }
    else
    {
        kdWarning(5003) << "unable to open " << f.name() << " reason " << f.status() << endl;
        return false;
    }
}