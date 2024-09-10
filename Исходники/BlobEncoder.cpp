template <> void
BlobEncoder::encode(const std::string &item)
{
    SAFEARRAYBOUND bound[1] = {0, 0};
    bound[0].cElements = item.size();
    blob = SafeArrayCreate(VT_UI1, 1, bound);
    if (S_OK != SafeArrayLock(blob)) {
        SafeArrayDestroy(blob);
        blob = 0;
        throw qpid::Exception("Error locking blob area for string");
    }
    memcpy_s(blob->pvData, item.size(), item.data(), item.size());
    this->vt = VT_ARRAY | VT_UI1;
    this->parray = blob;
    SafeArrayUnlock(blob);
}