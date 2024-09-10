QString CompressedWhitespace::compress(const QStringRef &input)
{
    Q_ASSERT(!isEven(1) && isEven(0) && isEven(2));
    Q_ASSERT(!input.isEmpty());

    QString result;
    const int len = input.length();

    /* The amount of compressed characters. For instance, if input is
     * four spaces followed by one tab, compressedChars will be 2, and the resulting
     * QString will have a length of 1, two compressedChars stored in one QChar. */
    int compressedChars = 0;

    for(int i = 0; i < len; ++i)
    {
        const QChar c(input.at(i));

        int start = i;

        while(true)
        {
            if(i + 1 == input.length() || input.at(i + 1) != c)
                break;
            else
                ++i;
        }

        /* The length of subsequent whitespace characters in the input. */
        int wsLen = (i - start) + 1;

        /* We might get a sequence of whitespace that is so long, that we can't
         * store it in one unit/byte. In that case we chop it into as many subsequent
         * ones that is needed. */
        while(true)
        {
            const int unitLength = qMin(wsLen, int(MaxCharCount));
            wsLen -= unitLength;

            ushort resultCP = toCompressedChar(c, unitLength);

            if(isEven(compressedChars))
                result += QChar(resultCP);
            else
            {
                resultCP = resultCP << 8;
                resultCP |= result.at(result.size() - 1).unicode();
                result[result.size() - 1] = resultCP;
            }

            ++compressedChars;

            if(wsLen == 0)
                break;
        }
    }

    return result;
}