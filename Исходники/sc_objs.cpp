void
ArrayObject::send()
{
    for (size_t i = 0; i < _objs.size(); i++) {
        Object* item = _objs[i];
        if (item->pyObject() == PyList_GetItem(_obj, i)) {
            item->send();
        }
    }
}