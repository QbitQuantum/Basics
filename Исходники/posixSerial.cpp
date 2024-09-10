int PosixSerial::initializePort()
{
    if(fd_ == -1) {
        if(openPort() == CROI_ERROR) {
            return CROI_ERROR;
        }
        if(configurePort() == CROI_ERROR) {
            return CROI_ERROR;
        }
    }
    initialized_ = true;
    return CROI_SUCCESS;
}