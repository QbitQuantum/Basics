void ThrowException(const wchar_t* szException)
{
    // We ignore error since we're already in an error state.
    JsValueRef errorValue;
    JsValueRef errorObject;
    JsPointerToString(szException, wcslen(szException), &errorValue);
    JsCreateError(errorValue, &errorObject);
    JsSetException(errorObject);
}