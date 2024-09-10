Boolean CUsbManager::PropertyContainsFunction(
    /* [in] */ const String& property,
    /* [in] */ const String& function)
{
    AutoPtr<ISystemProperties> sp;
    CSystemProperties::AcquireSingleton((ISystemProperties**)&sp);
    String functions;
    sp->Get(property, String(""), &functions);
    Int32 index = functions.IndexOf(function);

    if (index < 0) {
        return FALSE;
    }

    Char32 c1 = functions.GetChar(index - 1);
    if (index > 0 && c1 != ',') {
        return FALSE;
    }

    Int32 charAfter = index + function.GetLength();
    Char32 c2 = functions.GetChar(charAfter);
    if (charAfter < (Int32)functions.GetLength() && c2 != ',') {
        return FALSE;
    }

    return TRUE;
}