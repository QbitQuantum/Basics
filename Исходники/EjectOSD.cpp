wchar_t EjectOSD::MaskToDriveLetter(DWORD mask) {
    return (wchar_t) (log2(mask) + 65);
}