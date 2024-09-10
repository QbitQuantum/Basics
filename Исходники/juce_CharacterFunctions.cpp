juce_wchar CharacterFunctions::toLowerCase (const juce_wchar character) noexcept
{
    return (juce_wchar) towlower ((wint_t) character);
}