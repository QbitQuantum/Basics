void CWriteMasterBase::publish()
{
    if (published) return;
    published = true;
    if (!(diskHelperBase->getFlags() & (TDXtemporary|TDXjobtemp)))
        updateActivityResult(container.queryJob().queryWorkUnit(), diskHelperBase->getFlags(), diskHelperBase->getSequence(), fileName, recordsProcessed);

    IPropertyTree &props = fileDesc->queryProperties();
    props.setPropInt64("@recordCount", recordsProcessed);
    if (0 == (diskHelperBase->getFlags() & TDXtemporary) || container.queryJob().queryUseCheckpoints())
    {
        if (0 != (diskHelperBase->getFlags() & TDWexpires))
            setExpiryTime(props, diskHelperBase->getExpiryDays());
        if (TDWupdate & diskHelperBase->getFlags())
        {
            unsigned eclCRC;
            unsigned __int64 totalCRC;
            diskHelperBase->getUpdateCRCs(eclCRC, totalCRC);
            props.setPropInt("@eclCRC", eclCRC);
            props.setPropInt64("@totalCRC", totalCRC);
        }
    }
    container.queryTempHandler()->registerFile(fileName, container.queryOwner().queryGraphId(), diskHelperBase->getTempUsageCount(), TDXtemporary & diskHelperBase->getFlags(), getDiskOutputKind(diskHelperBase->getFlags()), &clusters);
    if (!dlfn.isExternal())
    {
        bool temporary = 0 != (diskHelperBase->getFlags()&TDXtemporary);
        if (!temporary && (queryJob().querySlaves() < fileDesc->numParts()))
        {
            // create empty parts for a fileDesc being published that is larger than this clusters
            size32_t recordSize = 0;
            IOutputMetaData *diskRowMeta = diskHelperBase->queryDiskRecordSize()->querySerializedDiskMeta();
            if (diskRowMeta->isFixedSize() && (TAKdiskwrite == container.getKind()))
            {
                recordSize = diskRowMeta->getMinRecordSize();
                if (0 != (diskHelperBase->getFlags() & TDXgrouped))
                    recordSize += 1;
            }
            unsigned compMethod = COMPRESS_METHOD_LZW;
            // rowdiff used if recordSize > 0, else fallback to compMethod
            if (getOptBool(THOROPT_COMP_FORCELZW, false))
            {
                recordSize = 0; // by default if fixed length (recordSize set), row diff compression is used. This forces compMethod.
                compMethod = COMPRESS_METHOD_LZW;
            }
            else if (getOptBool(THOROPT_COMP_FORCEFLZ, false))
                compMethod = COMPRESS_METHOD_FASTLZ;
            else if (getOptBool(THOROPT_COMP_FORCELZ4, false))
                compMethod = COMPRESS_METHOD_LZ4;
            bool blockCompressed;
            bool compressed = fileDesc->isCompressed(&blockCompressed);
            for (unsigned clusterIdx=0; clusterIdx<fileDesc->numClusters(); clusterIdx++)
            {
                StringBuffer clusterName;
                fileDesc->getClusterGroupName(clusterIdx, clusterName, &queryNamedGroupStore());
                PROGLOG("Creating blank parts for file '%s', cluster '%s'", fileName.get(), clusterName.str());
                unsigned p=0;
                while (p<fileDesc->numParts())
                {
                    if (p == targetOffset)
                        p += queryJob().querySlaves();
                    IPartDescriptor *partDesc = fileDesc->queryPart(p);
                    CDateTime createTime, modifiedTime;
                    for (unsigned c=0; c<partDesc->numCopies(); c++)
                    {
                        RemoteFilename rfn;
                        partDesc->getFilename(c, rfn);
                        StringBuffer path;
                        rfn.getPath(path);
                        try
                        {
                            ensureDirectoryForFile(path.str());
                            OwnedIFile iFile = createIFile(path.str());
                            Owned<IFileIO> iFileIO;
                            if (compressed)
                                iFileIO.setown(createCompressedFileWriter(iFile, recordSize, false, true, NULL, compMethod));
                            else
                                iFileIO.setown(iFile->open(IFOcreate));
                            dbgassertex(iFileIO.get());
                            iFileIO.clear();
                            // ensure copies have matching datestamps, as they would do normally (backupnode expects it)
                            if (partDesc->numCopies() > 1)
                            {
                                if (0 == c)
                                    iFile->getTime(&createTime, &modifiedTime, NULL);
                                else
                                    iFile->setTime(&createTime, &modifiedTime, NULL);
                            }
                        }
                        catch (IException *e)
                        {
                            if (0 == c)
                                throw;
                            Owned<IThorException> e2 = MakeThorException(e);
                            e->Release();
                            e2->setAction(tea_warning);
                            queryJob().fireException(e2);
                        }
                    }
                    partDesc->queryProperties().setPropInt64("@size", 0);
                    p++;
                }
                clusterIdx++;
            }
        }
        queryThorFileManager().publish(container.queryJob(), fileName, *fileDesc, NULL);
    }
}