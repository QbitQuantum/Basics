bool CharacterFunctions::isLowerCase (const beast_wchar character) noexcept
{
   #if BEAST_WINDOWS
    return iswlower ((wchar_t) character) != 0;
   #else
    return toUpperCase (character) != character;
   #endif
}