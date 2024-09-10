void helperPID::addVectorToOption(Bottle &option, const char *key, const Vector &val)
{
    Bottle &bKey=option.addList();
    bKey.addString(key);
    Bottle &bKeyContent=bKey.addList();
    for (size_t i=0; i<val.length(); i++)
        bKeyContent.addDouble(val[i]);
}