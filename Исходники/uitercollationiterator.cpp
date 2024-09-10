UChar32
UIterCollationIterator::previousCodePoint(UErrorCode & /*errorCode*/) {
    return uiter_previous32(&iter);
}