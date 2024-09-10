String getNormalizedPath(const String& path)
{
    // Full path is the fully qualified path from the root of the filesystem.  In order
    // to take advantage of the resource caching system, let's trim it down to just the
    // path inside the resources directory including the Resources directory so that the casing
    // is correct.
    const String& RESOURCES_MARKER = "resources/";
    return path.SubstringUTF8(path.ToLower().Find(RESOURCES_MARKER));
}