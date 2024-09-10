int main(int, char**)
{
    IDWriteFactory *factory = 0;
    DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,
                        __uuidof(IDWriteFactory),
                        reinterpret_cast<IUnknown **>(&factory));
    return 0;
}