// Compatibility hack for the Optimost Ti library. (See <rdar://problem/6595040>.)
static inline void insertSemicolonIfNeeded(UString& functionBody)
{
    ASSERT(functionBody[0] == '{');
    ASSERT(functionBody[functionBody.length() - 1] == '}');

    for (size_t i = functionBody.length() - 2; i > 0; --i) {
        UChar ch = functionBody[i];
        if (!Lexer::isWhiteSpace(ch) && !Lexer::isLineTerminator(ch)) {
            if (ch != ';' && ch != '}')
                functionBody = makeUString(functionBody.substringSharingImpl(0, i + 1), ";", functionBody.substringSharingImpl(i + 1, functionBody.length() - (i + 1)));
            return;
        }
    }
}