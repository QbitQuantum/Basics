    void GifImage::readMetadata()
    {
#ifdef DEBUG
        std::cerr << "Exiv2::GifImage::readMetadata: Reading GIF file " << io_->path() << "\n";
#endif
        if (io_->open() != 0)
        {
            throw Error(9, io_->path(), strError());
        }
        IoCloser closer(*io_);
        // Ensure that this is the correct image type
        if (!isGifType(*io_, true))
        {
            if (io_->error() || io_->eof()) throw Error(14);
            throw Error(3, "GIF");
        }
        clearMetadata();

        byte buf[4];
        if (io_->read(buf, sizeof(buf)) == sizeof(buf))
        {
            pixelWidth_ = getShort(buf, littleEndian);
            pixelHeight_ = getShort(buf + 2, littleEndian);
        }
    } // GifImage::readMetadata