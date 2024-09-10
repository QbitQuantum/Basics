// https://wicg.github.io/entries-api/#path-segment
static bool isValidPathSegment(StringView segment)
{
    if (segment.isEmpty() || segment == "." || segment == "..")
        return true;

    for (unsigned i = 0; i < segment.length(); ++i) {
        if (!isValidPathNameCharacter(segment[i]))
            return false;
    }
    return true;
}