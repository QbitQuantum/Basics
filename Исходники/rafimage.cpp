    void RafImage::readMetadata()
    {
#ifdef DEBUG
        std::cerr << "Reading RAF file " << io_->path() << "\n";
#endif
        if (io_->open() != 0) throw Error(9, io_->path(), strError());
        IoCloser closer(*io_);
        // Ensure that this is the correct image type
        if (!isRafType(*io_, false)) {
            if (io_->error() || io_->eof()) throw Error(14);
            throw Error(3, "RAF");
        }
        byte const* pData = io_->mmap();
        long size = io_->size();
        if (size < 88 + 4) throw Error(14); // includes the test for -1
        uint32_t const start = getULong(pData + 84, bigEndian) + 12;
        if (static_cast<uint32_t>(size) < start) throw Error(14);
        clearMetadata();
        ByteOrder bo = TiffParser::decode(exifData_,
                                          iptcData_,
                                          xmpData_,
                                          pData + start,
                                          size - start);

        exifData_["Exif.Image2.JPEGInterchangeFormat"] = getULong(pData + 84, bigEndian);
        exifData_["Exif.Image2.JPEGInterchangeFormatLength"] = getULong(pData + 88, bigEndian);

        setByteOrder(bo);
    } // RafImage::readMetadata