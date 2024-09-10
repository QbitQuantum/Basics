GenObject* HashList::remove(GenObject* obj, bool delobj, bool useHash)
{
    ObjList* n = 0;
    if (useHash && obj)
        n = find(obj,obj->toString().hash());
    else
        n = find(obj);
    return n ? n->remove(delobj) : 0;
}