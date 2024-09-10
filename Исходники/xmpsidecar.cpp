    void XmpSidecar::writeMetadata()
    {
        if (io_->open() != 0) {
            throw Error(9, io_->path(), strError());
        }
        IoCloser closer(*io_);

        if (writeXmpFromPacket() == false) {
            copyExifToXmp(exifData_, xmpData_);
            copyIptcToXmp(iptcData_, xmpData_);
            if (XmpParser::encode(xmpPacket_, xmpData_,
                                  XmpParser::omitPacketWrapper|XmpParser::useCompactFormat) > 1) {
#ifndef SUPPRESS_WARNINGS
                EXV_ERROR << "Failed to encode XMP metadata.\n";
#endif
            }
        }
        if (xmpPacket_.size() > 0) {
            if (xmpPacket_.substr(0, 5)  != "<?xml") {
                xmpPacket_ = xmlHeader + xmpPacket_;
            }
            BasicIo::AutoPtr tempIo(io_->temporary()); // may throw
            assert(tempIo.get() != 0);
            // Write XMP packet
            if (   tempIo->write(reinterpret_cast<const byte*>(xmpPacket_.data()),
                                 static_cast<long>(xmpPacket_.size()))
                != static_cast<long>(xmpPacket_.size())) throw Error(21);
            if (tempIo->error()) throw Error(21);
            io_->close();
            io_->transfer(*tempIo); // may throw
        }
    } // XmpSidecar::writeMetadata