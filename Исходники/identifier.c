Identifier *Identifier::generateId(const char *prefix, size_t i)
{   OutBuffer buf;

    buf.writestring(prefix);
    buf.printf("%llu", (ulonglong)i);

    char *id = buf.toChars();
    buf.data = NULL;
    return Lexer::idPool(id);
}