    void slaveDone(size32_t slaveIdx, MemoryBuffer &mb)
    {
        if (mb.length()) // if 0 implies aborted out from this slave.
        {
            rowcount_t slaveProcessed;
            mb.read(slaveProcessed);
            recordsProcessed += slaveProcessed;

            offset_t size, physicalSize;
            mb.read(size);
            mb.read(physicalSize);

            unsigned fileCrc;
            mb.read(fileCrc);

            CDateTime modifiedTime(mb);
            StringBuffer timeStr;
            modifiedTime.getString(timeStr);

            IPartDescriptor *partDesc = fileDesc->queryPart(slaveIdx);
            IPropertyTree &props = partDesc->queryProperties();
            props.setPropInt64("@size", size);
            if (fileDesc->isCompressed())
                props.setPropInt64("@compressedSize", physicalSize);
            props.setPropInt("@fileCrc", fileCrc);
            props.setProp("@modified", timeStr.str());
        }
    }