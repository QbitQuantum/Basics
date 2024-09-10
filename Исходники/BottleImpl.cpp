bool BottleImpl::fromBytes(const Bytes& data) {
    String wrapper(data.get(),data.length());
    StringInputStream sis;
    sis.add(wrapper);
    StreamConnectionReader reader;
    Route route;
    reader.reset(sis,NULL,route,data.length(),false);

    clear();
    dirty = true; // for clarity

    if (!nested) {
        
        clear();
        specialize(0);
        
        int code = reader.expectInt();
        if (reader.isError()) { return false; }
        YMSG(("READ got top level code %d\n", code));
        code = code & UNIT_MASK;
        if (code!=0) {
            specialize(code);
        }
    }
    int len = reader.expectInt();
    if (reader.isError()) { return false; }
    YMSG(("READ bottle length %d\n", len));
    for (int i=0; i<len; i++) {
        bool ok = fromBytes(reader);
        if (!ok) return false;
    }

    return true;
}