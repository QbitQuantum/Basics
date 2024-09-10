ActiveObject::~ActiveObject()
{
    if (cookie)
        RevokeActiveObject(cookie, 0);
    if (wrapper)
        wrapper->Release();
}