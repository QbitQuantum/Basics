void ImageMaker::stop() {
    CancelIoEx(m_driveHandle, nullptr);
    m_shouldHalt.signal();
}