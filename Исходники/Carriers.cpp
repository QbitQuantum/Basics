static bool matchCarrier(const Bytes *header, Bottle& code) {
    int at = 0;
    bool success = true;
    bool done = false;
    for (int i=0; i<code.size() && !done; i++) {
        Value& v = code.get(i);
        if (v.isString()) {
            ConstString str = v.asString();
            for (int j=0; j<(int)str.length(); j++) {
                if ((int)header->length()<=at) {
                    success = false;
                    done = true;
                    break;
                }
                if (str[j] != header->get()[at]) {
                    success = false;
                    done = true;
                    break;
                }
                at++;
            }
        } else {
            at++;
        }
    }
    return success;
}