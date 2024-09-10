/**
 Gets the value of the specified \p key of the document information.

 \returns the value for the \p key, or an empty string if not available
 \see info_keys, info_date
 */
ustring document::info_key(const std::string &key) const
{
    if (d->is_locked) {
        return ustring();
    }

    Object info;
    if (!d->doc->getDocInfo(&info)->isDict()) {
        info.free();
        return ustring();
    }

    Dict *info_dict = info.getDict();
    Object obj;
    ustring result;
    if (info_dict->lookup(PSTR(key.c_str()), &obj)->isString()) {
        result = detail::unicode_GooString_to_ustring(obj.getString());
    }
    obj.free();
    info.free();
    return result;
}