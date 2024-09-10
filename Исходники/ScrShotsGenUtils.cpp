TBool ScrShotsGenUtils::CheckIfAppExists(const TDesC& aAppName, const TUid& aAppUid)
{
    TBool appFound = EFalse;
    RApaLsSession appLs;
    if(appLs.Connect()==KErrNone){
        appLs.GetAllApps();
        TApaAppInfo dummyAppInfo;
        while(appLs.GetNextApp(dummyAppInfo)!= RApaLsSession::ENoMoreAppsInList){
            if(dummyAppInfo.iShortCaption[0] == '!' || dummyAppInfo.iShortCaption.Length() == 0)
                continue;
            TStringPoolObj fullName(512);
            fullName.Des().Copy(dummyAppInfo.iFullName);
            fullName.Des().LowerCase();
            //we dont want to show Brahma in the app list.
            if(dummyAppInfo.iUid == KBrahmaUid)
                continue;
            //filtering out midlets (.fakeapp) & wrt widgets (.html)
            if(fullName.Des().Find(_L(".fakeapp")) != KErrNotFound || fullName.Des().Find(_L(".html")) != KErrNotFound)
                continue;
            TApaAppCapabilityBuf appCap;
            if(appLs.GetAppCapability(appCap, dummyAppInfo.iUid) == KErrNone){
                //if its hidden its a ui app 
                if(appCap().iAppIsHidden || appCap().iAttributes == TApaAppCapability::EControlPanelItem)
                    continue;
            }
            if(dummyAppInfo.iCaption.Compare(aAppName) == 0 &&  dummyAppInfo.iUid == aAppUid){
                appFound = ETrue;
                break;
            }
        }
        appLs.Close();
    }
    return appFound;
}