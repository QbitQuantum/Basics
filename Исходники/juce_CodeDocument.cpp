void CodeDocument::replaceAllContent (const String& newContent)
{
    remove (0, getNumCharacters(), true);
    insert (newContent, 0, true);
}