extern "C" errno_t __cdecl wmemmove_s(
    wchar_t*       const destination,
    size_t         const size_in_elements,
    wchar_t const* const source,
    size_t         const count
    )
{
    if (count == 0)
        return 0;

#pragma warning(suppress:__WARNING_HIGH_PRIORITY_OVERFLOW_POSTCONDITION)
    _VALIDATE_RETURN_ERRCODE(destination != nullptr, EINVAL);
    _VALIDATE_RETURN_ERRCODE(source != nullptr, EINVAL);
    _VALIDATE_RETURN_ERRCODE(size_in_elements >= count, ERANGE);

#pragma warning(suppress:__WARNING_BANNED_API_USAGEL2 __WARNING_BUFFER_COPY_NO_KNOWN_SIZEEXPR) /* 28726 22104 */
    wmemmove(destination, source, count);
    return 0;
}