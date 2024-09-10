void yarp::os::impl::NameserCarrier::getHeader(const Bytes& header) {
    if (header.length()==8) {
        String target = getSpecifierName();
        for (int i=0; i<8; i++) {
            header.get()[i] = target[i];
        }
    }
}