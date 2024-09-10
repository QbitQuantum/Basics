Bool testhash::Parent::insertChild(const Child & child, Sym key, Bool replace) const  {
    if(!child.isExists() || child.getParent().isValid() || (!replace && hasKeyChild(key)))
        return false;
    if (getChildTableLen() == 0)
    {
        resizeChildTable(getChildTableSize());
        for (StdUInt i = 0; i < getChildTableSize(); i++)
            setiChildTable(i, Child());
    }
    StdUInt hash_value = getChildHash(key);
    Child first_table_child = getiChildTable(hash_value);
    if (first_table_child.isValid())
        insertBeforeTableListChild(child, first_table_child);
    else
    {
        if (hash_value < getChildTableMin())
        {
            pushFrontTableListChild(child);
            setChildTableMin(hash_value);
        }
        else if (hash_value > getChildTableMax())
        {
            pushBackTableListChild(child);
            setChildTableMax(hash_value);
        }
        else
        {
            StdUInt next_busy;
            for (next_busy = hash_value + 1; next_busy <= getChildTableMax(); next_busy++)
            {
                Child next_table_child = getiChildTable(next_busy);
                if (next_table_child.isValid())
                {
                    insertBeforeTableListChild(child, next_table_child);
                    break;
                }
            }
        }
    }
    setiChildTable(hash_value, child);
    setNumChilds(getNumChilds() + 1);
    child.setParentKey(key);
    child.setParent(*this);
    child.setupParentHandler();
    return true;
}