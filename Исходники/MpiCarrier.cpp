 bool MpiCarrier::checkHeader(const Bytes& header) {
    if (header.length()!=8) {
        return false;
    }
    for (int i=0; i<8; i++) {
        if (header.get()[i] != target.c_str()[i]) {
            return false;
        }
    }
    return true;
}