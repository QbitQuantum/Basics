//==============================================================================
static String removeEllipsis (const String& path)
{
    // This will quickly find both /../ and /./ at the expense of a minor
    // false-positive performance hit when path elements end in a dot.
   #if JUCE_WINDOWS
    if (path.contains (".\\"))
   #else
    if (path.contains ("./"))
   #endif
    {
        StringArray toks;
        toks.addTokens (path, File::getSeparatorString(), {});
        bool anythingChanged = false;

        for (int i = 1; i < toks.size(); ++i)
        {
            auto& t = toks[i];

            if (t == ".." && toks[i - 1] != "..")
            {
                anythingChanged = true;
                toks.removeRange (i - 1, 2);
                i = jmax (0, i - 2);
            }
            else if (t == ".")
            {
                anythingChanged = true;
                toks.remove (i--);
            }
        }

        if (anythingChanged)
            return toks.joinIntoString (File::getSeparatorString());
    }

    return path;
}