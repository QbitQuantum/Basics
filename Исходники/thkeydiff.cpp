    virtual void done()
    {
        StringBuffer scopedName;
        OwnedRoxieString outputName(helper->getOutputName());
        queryThorFileManager().addScope(container.queryJob(), outputName, scopedName);
        Owned<IWorkUnit> wu = &container.queryJob().queryWorkUnit().lock();
        Owned<IWUResult> r = wu->updateResultBySequence(helper->getSequence());
        r->setResultStatus(ResultStatusCalculated);
        r->setResultLogicalName(scopedName.str());
        r.clear();
        wu.clear();

        IPropertyTree &patchProps = patchDesc->queryProperties();
        if (0 != (helper->getFlags() & KDPexpires))
            setExpiryTime(patchProps, helper->getExpiryDays());
        IPropertyTree &originalProps = originalDesc->queryProperties();;
        if (originalProps.queryProp("ECL"))
            patchProps.setProp("ECL", originalProps.queryProp("ECL"));
        if (originalProps.getPropBool("@local"))
            patchProps.setPropBool("@local", true);
        container.queryTempHandler()->registerFile(outputName, container.queryOwner().queryGraphId(), 0, false, WUFileStandard, &clusters);
        Owned<IDistributedFile> patchFile;
        // set part sizes etc
        queryThorFileManager().publish(container.queryJob(), outputName, false, *patchDesc, &patchFile, 0, false);
        try { // set file size
            if (patchFile) {
                __int64 fs = patchFile->getFileSize(true,false);
                if (fs!=-1)
                    patchFile->queryAttributes().setPropInt64("@size",fs);
            }
        }
        catch (IException *e) {
            EXCLOG(e,"keydiff setting file size");
            e->Release();
        }
        // Add a new 'Patch' description to the secondary key.
        DistributedFilePropertyLock lock(newIndexFile);
        IPropertyTree &fileProps = lock.queryAttributes();
        StringBuffer path("Patch[@name=\"");
        path.append(scopedName.str()).append("\"]");
        IPropertyTree *patch = fileProps.queryPropTree(path.str());
        if (!patch) patch = fileProps.addPropTree("Patch", createPTree());
        patch->setProp("@name", scopedName.str());
        unsigned checkSum;
        if (patchFile->getFileCheckSum(checkSum))
            patch->setPropInt64("@checkSum", checkSum);

        IPropertyTree *index = patch->setPropTree("Index", createPTree());
        index->setProp("@name", originalIndexFile->queryLogicalName());
        if (originalIndexFile->getFileCheckSum(checkSum))
            index->setPropInt64("@checkSum", checkSum);
        originalIndexFile->setAccessed();
        newIndexFile->setAccessed();
    }