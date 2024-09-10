GenObject* ObjList::remove(const String& str, bool delobj)
{
    ObjList *n = find(str);
    return n ? n->remove(delobj) : 0;
}