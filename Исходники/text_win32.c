void loadFontFromMemory(void* font_data, int num_bytes) {
    DWORD one = 1;
    assert(AddFontMemResourceEx(font_data, num_bytes, 0, &one));
}