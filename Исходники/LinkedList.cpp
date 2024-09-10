/*---------------------------------------------------------LinkedList::remove-+
|                                                                             |
+----------------------------------------------------------------------------*/
bool LinkedList::remove(int index) {
    Item * what = get(index);
    if (what == 0) return false;
    what->unlink(m_size);
    return true;
}