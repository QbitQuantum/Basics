String extractMIMETypeFromMediaType(const String& mediaType)
{
    StringBuilder mimeType;
    unsigned length = mediaType.length();
    mimeType.reserveCapacity(length);
    for (unsigned i = 0; i < length; i++) {
        UChar c = mediaType[i];

        if (c == ';')
            break;

        // While RFC 2616 does not allow it, other browsers allow multiple values in the HTTP media
        // type header field, Content-Type. In such cases, the media type string passed here may contain
        // the multiple values separated by commas. For now, this code ignores text after the first comma,
        // which prevents it from simply failing to parse such types altogether. Later for better
        // compatibility we could consider using the first or last valid MIME type instead.
        // See https://bugs.webkit.org/show_bug.cgi?id=25352 for more discussion.
        if (c == ',')
            break;

        // FIXME: The following is not correct. RFC 2616 allows linear white space before and
        // after the MIME type, but not within the MIME type itself. And linear white space
        // includes only a few specific ASCII characters; a small subset of isSpaceOrNewline.
        // See https://bugs.webkit.org/show_bug.cgi?id=8644 for a bug tracking part of this.
        if (isSpaceOrNewline(c))
            continue;

        mimeType.append(c);
    }

    if (mimeType.length() == length)
        return mediaType;
    return mimeType.toString();
}