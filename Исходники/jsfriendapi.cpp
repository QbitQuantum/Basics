js::DumpChars(const char16_t* s, size_t n, js::GenericPrinter& out)
{
    out.printf("char16_t * (%p) = ", (void*) s);
    JSString::dumpChars(s, n, out);
    out.putChar('\n');
}