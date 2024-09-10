String TextCheckingHelper::findFirstMisspelling(int& firstMisspellingOffset, bool markAll, RefPtr<Range>& firstMisspellingRange)
{
    WordAwareIterator it(*m_range);
    firstMisspellingOffset = 0;
    
    String firstMisspelling;
    int currentChunkOffset = 0;

    while (!it.atEnd()) {
        StringView text = it.text();
        int textLength = text.length();

        // Skip some work for one-space-char hunks
        if (textLength == 1 && text[0] == ' ') {
            int misspellingLocation = -1;
            int misspellingLength = 0;
            m_client->textChecker()->checkSpellingOfString(text, &misspellingLocation, &misspellingLength);

            // 5490627 shows that there was some code path here where the String constructor below crashes.
            // We don't know exactly what combination of bad input caused this, so we're making this much
            // more robust against bad input on release builds.
            ASSERT(misspellingLength >= 0);
            ASSERT(misspellingLocation >= -1);
            ASSERT(!misspellingLength || misspellingLocation >= 0);
            ASSERT(misspellingLocation < textLength);
            ASSERT(misspellingLength <= textLength);
            ASSERT(misspellingLocation + misspellingLength <= textLength);

            if (misspellingLocation >= 0 && misspellingLength > 0 && misspellingLocation < textLength && misspellingLength <= textLength && misspellingLocation + misspellingLength <= textLength) {
                // Compute range of misspelled word
                RefPtr<Range> misspellingRange = TextIterator::subrange(m_range.get(), currentChunkOffset + misspellingLocation, misspellingLength);

                // Remember first-encountered misspelling and its offset.
                if (!firstMisspelling) {
                    firstMisspellingOffset = currentChunkOffset + misspellingLocation;
                    firstMisspelling = text.substring(misspellingLocation, misspellingLength).toString();
                    firstMisspellingRange = misspellingRange;
                }

                // Store marker for misspelled word.
                misspellingRange->startContainer()->document().markers().addMarker(misspellingRange.get(), DocumentMarker::Spelling);

                // Bail out if we're marking only the first misspelling, and not all instances.
                if (!markAll)
                    break;
            }
        }
        
        currentChunkOffset += textLength;
        it.advance();
    }
    
    return firstMisspelling;
}