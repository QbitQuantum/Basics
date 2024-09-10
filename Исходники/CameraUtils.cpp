jderobot::ImageDataPtr CameraUtils::convert(const cv::Mat &image) {

    jderobot::ImageDataPtr reply=jderobot::ImageDataPtr(new jderobot::ImageData());
    reply->description = jderobot::ImageDescriptionPtr(new jderobot::ImageDescription());
    IceUtil::Time t = IceUtil::Time::now();
    reply->timeStamp.seconds = (long)t.toSeconds();
    reply->timeStamp.useconds = (long)t.toMicroSeconds() - reply->timeStamp.seconds*1000000;
    reply->description->format = colorspaces::ImageRGB8::FORMAT_RGB8.get()->name;
    reply->description->width=image.size().width;
    reply->description->height=image.size().height;
    reply->pixelData.resize(image.rows*image.cols * image.channels());
    memcpy(&(reply->pixelData[0]),(unsigned char *) image.data, image.rows*image.cols * image.channels());
    return reply;
}