int32_t RuleBasedCollator::getSortKey(const UnicodeString& source,
                                         uint8_t *result, int32_t resultLength)
                                         const
{
    return ucol_getSortKey(ucollator, source.getBuffer(), source.length(), result, resultLength);
}