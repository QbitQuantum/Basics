void XmlDocument::readQuotedString (String& result)
{
    const juce_wchar quote = readNextChar();

    while (! outOfData)
    {
        const juce_wchar c = readNextChar();

        if (c == quote)
            break;

        --input;

        if (c == '&')
        {
            readEntity (result);
        }
        else
        {
            const String::CharPointerType start (input);

            for (;;)
            {
                const juce_wchar character = *input;

                if (character == quote)
                {
                    result.appendCharPointer (start, input);
                    ++input;
                    return;
                }
                else if (character == '&')
                {
                    result.appendCharPointer (start, input);
                    break;
                }
                else if (character == 0)
                {
                    outOfData = true;
                    setLastError ("unmatched quotes", false);
                    break;
                }

                ++input;
            }
        }
    }
}