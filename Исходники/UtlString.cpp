// Return the index of the designated substring starting at the
// designated position or UTLSTRING_NOT_FOUND  if not found.
// Optimization to avoid strlen call as well as the only
// safe way to work with binary or opaque data
size_t UtlString::index(const UtlString& searchString, size_t start, CompareCase type) const
{
    size_t foundPosition = UTLSTRING_NOT_FOUND;
    size_t searchStrSize = searchString.length();
    size_t startIndex = start;

    if (type == matchCase)
    {

        foundPosition = index(searchString, start);
    }
    else
    {
        // mpData may be null, so use data() which returns an
        // static empty string if mpData is null
        const char* dataPtr = data();

        if(searchStrSize <= mSize)
        {
            for (size_t pos = startIndex;
                 pos <= (mSize - searchStrSize)
                 && foundPosition == UTLSTRING_NOT_FOUND;
                 pos++)
            {
#ifdef WIN32
                if (strnicmp(dataPtr + pos,
                             searchString.data(),
                             searchStrSize) == 0)
#else
                if(strncasecmp(dataPtr + pos,
                               searchString.data(),
                               searchStrSize) == 0)
#endif
                {
                    foundPosition = pos;
                }
            }
        }
    }

    return foundPosition;
}