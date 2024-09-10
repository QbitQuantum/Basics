PassRefPtr<DOMStringList> toDOMStringList(ExecState* exec, JSValue value)
{
    if (value.inherits(&JSDOMStringList::s_info))
        return jsCast<JSDOMStringList*>(asObject(value))->impl();

    if (!isJSArray(value))
        return 0;

    JSArray* array = asArray(value);
    RefPtr<DOMStringList> stringList = DOMStringList::create();
    for (unsigned i = 0; i < array->length(); ++i)
        stringList->append(array->getIndex(exec, i).toString(exec)->value(exec));

    return stringList.release();
}