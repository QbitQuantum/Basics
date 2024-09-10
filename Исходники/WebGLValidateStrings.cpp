bool
TruncateComments(const nsAString& src, nsAString* const out)
{
    const size_t dstByteCount = src.Length() * sizeof(src[0]);
    const UniqueBuffer dst(malloc(dstByteCount));
    if (!dst)
        return false;

    auto srcItr = src.BeginReading();
    const auto srcEnd = src.EndReading();
    const auto dstBegin = (decltype(src[0])*)dst.get();
    auto dstItr = dstBegin;

    const auto fnEmitUntil = [&](const decltype(srcItr)& nextSrcItr) {
        while (srcItr != nextSrcItr) {
            *dstItr = *srcItr;
            ++srcItr;
            ++dstItr;
        }
    };

    const auto fnFindSoonestOf = [&](const nsString* needles, size_t needleCount,
                                     size_t* const out_foundId)
    {
        auto foundItr = srcItr;
        while (foundItr != srcEnd) {
            const auto haystack = Substring(foundItr, srcEnd);
            for (size_t i = 0; i < needleCount; i++) {
                if (StringBeginsWith(haystack, needles[i])) {
                    *out_foundId = i;
                    return foundItr;
                }
            }
            ++foundItr;
        }
        *out_foundId = needleCount;
        return foundItr;
    };

    ////

    const nsString commentBeginnings[] = { NS_LITERAL_STRING("//"),
                                           NS_LITERAL_STRING("/*"),
                                           nsString() }; // Final empty string for "found
                                                         // nothing".
    const nsString lineCommentEndings[] = { NS_LITERAL_STRING("\\\n"),
                                            NS_LITERAL_STRING("\n"),
                                            nsString() };
    const nsString blockCommentEndings[] = { NS_LITERAL_STRING("\n"),
                                             NS_LITERAL_STRING("*/"),
                                             nsString() };

    while (srcItr != srcEnd) {
        size_t foundId;
        fnEmitUntil( fnFindSoonestOf(commentBeginnings, 2, &foundId) );
        fnEmitUntil(srcItr + commentBeginnings[foundId].Length()); // Final empty string
                                                                   // allows us to skip
                                                                   // forward here
                                                                   // unconditionally.
        switch (foundId) {
        case 0: // line comment
            while (true) {
                size_t endId;
                srcItr = fnFindSoonestOf(lineCommentEndings, 2, &endId);
                fnEmitUntil(srcItr + lineCommentEndings[endId].Length());
                if (endId == 0)
                    continue;
                break;
            }
            break;

        case 1: // block comment
            while (true) {
                size_t endId;
                srcItr = fnFindSoonestOf(blockCommentEndings, 2, &endId);
                fnEmitUntil(srcItr + blockCommentEndings[endId].Length());
                if (endId == 0)
                    continue;
                break;
            }
            break;

        default: // not found
            break;
        }
    }

    MOZ_ASSERT((dstBegin+1) - dstBegin == 1);
    const uint32_t dstCharLen = dstItr - dstBegin;
    if (!out->Assign(dstBegin, dstCharLen, mozilla::fallible))
        return false;

    return true;
}