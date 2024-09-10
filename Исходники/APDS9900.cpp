bool APDS9900::testConnection() {
    return getDeviceID() == 0x29;
}