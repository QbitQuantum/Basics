static String fixLineEndings (const String& s)
{
    StringArray lines;
    lines.addLines (s);

    for (int i = 0; i < lines.size(); ++i)
        lines.set (i, lines[i].trimEnd());

    while (lines.size() > 0 && lines [lines.size() - 1].trim().isEmpty())
        lines.remove (lines.size() - 1);

    lines.add (String::empty);

    return lines.joinIntoString ("\r\n");
}