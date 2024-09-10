std::u16string BiDi::writeReverse(const std::u16string& input, std::size_t logicalStart, std::size_t logicalEnd) {
    UErrorCode errorCode = U_ZERO_ERROR;
    int32_t logicalLength = static_cast<int32_t>(logicalEnd - logicalStart);
    std::u16string outputText(logicalLength + 1, 0);
    
    // UBIDI_DO_MIRRORING: Apply unicode mirroring of characters like parentheses
    // UBIDI_REMOVE_BIDI_CONTROLS: Now that all the lines are set, remove control characters so that
    // they don't show up on screen (some fonts have glyphs representing them)
    int32_t outputLength =
        ubidi_writeReverse(mbgl::utf16char_cast<const UChar*>(&input[logicalStart]),
                           logicalLength,
                           mbgl::utf16char_cast<UChar*>(&outputText[0]),
                           logicalLength + 1, // Extra room for null terminator, although we don't really need to have ICU write it for us
                           UBIDI_DO_MIRRORING | UBIDI_REMOVE_BIDI_CONTROLS,
                           &errorCode);
    
    if (U_FAILURE(errorCode)) {
        throw std::runtime_error(std::string("BiDi::writeReverse: ") + u_errorName(errorCode));
    }
    
    outputText.resize(outputLength); // REMOVE_BIDI_CONTROLS may have shrunk the string

    return outputText;
}