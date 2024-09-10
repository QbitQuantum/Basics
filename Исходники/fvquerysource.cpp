bool QueryDataSource::createBrowseWU()
{
    StringAttr dataset, datasetDefs;
    StringAttrAdaptor a1(dataset), a2(datasetDefs);
    wuResult->getResultDataset(a1, a2);

    if (!dataset || !datasetDefs)
        return false;
    StringBuffer fullText;
    fullText.append(datasetDefs).append(dataset);
    OwnedHqlExpr parsed = parseQuery(fullText.str());
    if (!parsed)
        return false;

    HqlExprAttr selectFields = parsed.getLink();
    if (selectFields->getOperator() == no_output)
        selectFields.set(selectFields->queryChild(0));

    OwnedHqlExpr browseWUcode = buildQueryViewerEcl(selectFields);
    if (!browseWUcode)
        return false;
    returnedRecord.set(browseWUcode->queryChild(0)->queryRecord());

    StringAttr tempAttr;
    StringAttrAdaptor temp(tempAttr);
    Owned<IWorkUnitFactory> factory = getWorkUnitFactory();
    Owned<IConstWorkUnit> parent = factory->openWorkUnit(wuid, false);

    SCMStringBuffer user;
    StringAttrAdaptor acluster(cluster);
    parent->getClusterName(acluster);
    parent->getUser(user);

    Owned<IWorkUnit> workunit = factory->createWorkUnit(NULL, "fileViewer", user.str());
    workunit->setUser(user.str());
    workunit->setClusterName(cluster);
    workunit->setCustomerId(parent->getCustomerId(temp).str());
    workunit->setCompareMode(CompareModeOff);   // ? parent->getCompareMode()
    StringAttrAdaptor bwa(browseWuid); workunit->getWuid(bwa);

    workunit->setDebugValueInt("importImplicitModules", false, true);
    workunit->setDebugValueInt("importAllModules", false, true);
    workunit->setDebugValueInt("forceFakeThor", 1, true);

    StringBuffer jobName;
    jobName.append("FileView for ").append(wuid).append(":").append("x");
    workunit->setJobName(jobName.str());

    StringBuffer eclText;
    toECL(browseWUcode, eclText, true);
    Owned<IWUQuery> query = workunit->updateQuery();
    query->setQueryText(eclText.str());
    query->setQueryName(jobName.str());

    return true;
}