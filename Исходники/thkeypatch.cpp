    virtual void slaveDone(size32_t slaveIdx, MemoryBuffer &mb)
    {
        if (mb.length()) // if 0 implies aborted out from this slave.
        {
            offset_t size;
            mb.read(size);
            CDateTime modifiedTime(mb);

            IPartDescriptor *partDesc = newIndexDesc->queryPart(slaveIdx);
            IPropertyTree &props = partDesc->queryProperties();
            props.setPropInt64("@size", size);
            StringBuffer timeStr;
            modifiedTime.getString(timeStr);
            props.setProp("@modified", timeStr.str());
            if (!local && 0 == slaveIdx)
            {
                mb.read(size);
                CDateTime modifiedTime(mb);
                IPartDescriptor *partDesc = newIndexDesc->queryPart(newIndexDesc->numParts()-1);
                IPropertyTree &props = partDesc->queryProperties();
                props.setPropInt64("@size", size);
                StringBuffer timeStr;
                modifiedTime.getString(timeStr);
                props.setProp("@modified", timeStr.str());
            }
        }
    }