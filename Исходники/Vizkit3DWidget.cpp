    void operator()(const osg::Image& image, const unsigned int)
    {
        frame_id++;

        QImage::Format qtFormat;
        if (image.getPixelFormat() == GL_BGR)
            qtFormat = QImage::Format_RGB888;
        else if (image.getPixelFormat() == GL_BGRA)
            qtFormat = QImage::Format_ARGB32;
        else if (image.getPixelFormat() == GL_RGB)
            qtFormat = QImage::Format_RGB888;
        else if (image.getPixelFormat() == GL_RGBA)
            qtFormat = QImage::Format_ARGB32;
        else
            throw std::runtime_error("cannot interpret osg-provided image format " +
                    boost::lexical_cast<std::string>(image.getPixelFormat()));

        this->image = QImage(image.data(), image.s(), image.t(), qtFormat);
    }