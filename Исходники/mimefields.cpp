UString MimeField::value() const
{
    Utf8Codec c;
    return c.toUnicode( rfc822() );
    // the best that can be said about this is that it corresponds to
    // HeaderField::assemble.
}