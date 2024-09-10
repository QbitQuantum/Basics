NetListener::~NetListener() {
    NetworkDevice* nd = NetworkDevice::instance();
    nd->closesocket(sock);
}