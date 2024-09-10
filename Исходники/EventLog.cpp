void EventLog::TagBuffer::writeString8(const String8& value) {
    if (mOverflow) return;
    const int32_t stringLen = value.length();
    const size_t needed = 1 + sizeof(int32_t) + stringLen;
    if (mPos + needed > STORAGE_MAX_SIZE) {
        mOverflow = true;
        return;
    }
    mStorage[mPos + 0] = EVENT_TYPE_STRING;
    memcpy(&mStorage[mPos + 1], &stringLen, sizeof(int32_t));
    memcpy(&mStorage[mPos + 5], value.string(), stringLen);
    mPos += needed;
}