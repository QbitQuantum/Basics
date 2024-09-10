void TouchTracking::initializeVideo()
{
    OpenNI::initialize();

    if (device.open(ANY_DEVICE) != STATUS_OK)
    {
        throw std::runtime_error("could not open any device!");
    }

    if (!device.hasSensor(SENSOR_DEPTH))
    {
        throw std::runtime_error("sensor cannot receive depth!");
    }

    auto info = device.getSensorInfo(SENSOR_DEPTH);
    auto& modes = info->getSupportedVideoModes();
    //std::cout << "depth sensor supported modes:\r\n";
    for (int i = 0; i < modes.getSize(); ++i)
    {
        m_videoModes.push_back(modes[i]);
        //std::cout << "pixel format: " << mode.getPixelFormat() << "\t with: " << mode.getResolutionX() << "x" << mode.getResolutionY() << "@" << mode.getFps() << " fps\r\n";
    }

    VideoMode mode;
    mode.setFps(60);
    mode.setPixelFormat(PIXEL_FORMAT_DEPTH_1_MM);
    mode.setResolution(320, 240);
    videoMode(mode);

    stream.setMirroringEnabled(false);
}