// ---------------------------------------------------------
// CPosLmDatabaseManagerImpl::ListDatabasesL
//
// (other items were commented in a header).
// ---------------------------------------------------------
//
void CPosLmDatabaseManagerImpl::ListDatabasesL(
    RPointerArray<HPosLmDatabaseInfo>& aDatabaseInfoArray,
    const TDesC& aProtocol)
    {
    if (aProtocol == KNullDesC)
        {
        TInt pluginCount = iPlugins->NumberOfInstances();
        for (TInt i = 0; i < pluginCount; i++)
            {
            if (i == 0)
                {
                CPosLmDatabaseManagerPluginBase* plugin =
                    iPlugins->GetInstanceAt(i);
                plugin->ListDatabasesL(aDatabaseInfoArray);
                FillInDbInfoListL(aDatabaseInfoArray, plugin);
                }
            else
                {
                RPointerArray<HPosLmDatabaseInfo> dbList;
                CleanupStack::PushL(TCleanupItem(CleanupPointerArray, &dbList));
                CPosLmDatabaseManagerPluginBase* plugin =
                    iPlugins->GetInstanceAt(i);
                plugin->ListDatabasesL(dbList);
                FillInDbInfoListL(dbList, plugin);
                TInt dbCount = dbList.Count();
                for (TInt j = 0; j < dbCount; j++)
                    {
                    // transfer ownership instead of copy object
                    User::LeaveIfError(aDatabaseInfoArray.Append(dbList[0]));
                    dbList.Remove(0);
                    }
                CleanupStack::PopAndDestroy(&dbList);
                }
            }
        }
    else
        {
        CPosLmDatabaseManagerPluginBase* plugin =
            iPlugins->GetInstanceL(aProtocol);
        plugin->ListDatabasesL(aDatabaseInfoArray);
        FillInDbInfoListL(aDatabaseInfoArray, plugin);
        }
    }