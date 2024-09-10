bool databaseFile:: isNumber(QString strCheck)
{
    int strLen = strCheck.length();
    if(strLen==0)
        return false;
    for(int i=0; i<strLen; i++)
    {
        QChar ch = strCheck.at(i);
        if(ch.isDigit() == false)
            return false;
    }
    return true;
}