ECode CEmojiFactory::GetAndroidPuaFromVendorSpecificPua(
    /* [in] */ const String& vspString,
    /* [out] */ String* retValue)
{
    VALIDATE_NOT_NULL(retValue);
    *retValue = NULL;

    if (vspString.IsNull()) {
        return E_NULL_POINTER_EXCEPTION;
    }

    Int32 minVsp = NativeGetMinimumVendorSpecificPua(mNativeEmojiFactory);
    Int32 maxVsp = NativeGetMaximumVendorSpecificPua(mNativeEmojiFactory);

    AutoPtr<ArrayOf<Int32> > codePoints = ArrayOf<Int32>::Alloc(vspString.GetCharCount(0, len));\
    Int32 new_len = 0;

    for (Int32 i=0; i < len; i++,new_len++)
        Int32 codePoint = (Int32)vspString.GetChar(i);
        if (minVsp <= codePoint && codePoint <= maxVsp) {
            Int32 newCodePoint = GetAndroidPuaFromVendorSpecificPua(codePoint);
            if (newCodePoint > 0) {
                    (*codePoints)[new_len] = newCodePoint;
                    continue;
            }
        }
        (*codePoints)[new_len] = codePoint;
    }