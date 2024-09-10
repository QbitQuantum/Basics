int findNextWordFromIndex(const UChar* chars, int len, int position, bool forward)
{
    TextBreakIterator* it = wordBreakIterator(chars, len);

    if (forward) 
    {
        position = textBreakFollowing(it, position);
        while (position != -1) 
        {
            // We stop searching when the character preceeding the break
            // is alphanumeric.
            if (position < len && iswalpha(chars[position - 1]))
                return position;

            position = textBreakFollowing(it, position);
        }

        return len;
    } 
    else 
    {
        position = textBreakPreceding(it, position);
        while (position != -1) 
        {
            // We stop searching when the character following the break
            // is alphanumeric.
            if (position > 0 && iswalpha(chars[position]))
                return position;

            position = textBreakPreceding(it, position);
        }

        return 0;
    }
}