void ff2LayNN::setItem(Property &options, const string &tag, const Vector &item) const
{
    Bottle b; Bottle &v=b.addList();
    for (size_t i=0; i<item.length(); i++)
        v.addDouble(item[i]);

    options.put(tag.c_str(),b.get(0));
}