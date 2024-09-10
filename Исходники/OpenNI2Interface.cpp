void OpenNI2Interface::printMode(const openni::VideoMode& mode)
{
    std::map<int,std::string> formatNames;
    formatNames[openni::PIXEL_FORMAT_DEPTH_1_MM] = "1mm";
    formatNames[openni::PIXEL_FORMAT_DEPTH_100_UM] = "100um";
    formatNames[openni::PIXEL_FORMAT_SHIFT_9_2] = "Shift 9 2";
    formatNames[openni::PIXEL_FORMAT_SHIFT_9_3] = "Shift 9 3";

    formatNames[openni::PIXEL_FORMAT_RGB888] = "RGB888";
    formatNames[openni::PIXEL_FORMAT_YUV422] = "YUV422";
    formatNames[openni::PIXEL_FORMAT_GRAY8] = "GRAY8";
    formatNames[openni::PIXEL_FORMAT_GRAY16] = "GRAY16";
    formatNames[openni::PIXEL_FORMAT_JPEG] = "JPEG";

    cout << "(" << mode.getResolutionX() << "x" << mode.getResolutionY()
        << ", " << mode.getFps() << " fps, " << formatNames[mode.getPixelFormat()] << ")\n";
}