bool yarp::os::impl::LocalCarrier::checkHeader(const Bytes& header) {
    if (header.length()==8) {
        std::string target = getSpecifierName();
        for (int i=0; i<8; i++) {
            if (!(target[i]==header.get()[i])) {
                return false;
            }
        }
        return true;
    }
    return false;
}