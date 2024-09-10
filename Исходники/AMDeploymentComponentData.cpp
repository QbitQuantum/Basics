TUid CDeploymentComponentData::SetDataL(const TDesC8& aMimeType)
    {
    RDEBUG8_2("CDeploymentComponentData::SetDataL() aMimeType: (%S)", &aMimeType);

    TUid ret(TUid::Null());
    iMimeType = aMimeType.Left(KMaxMimeLength);

    if (aMimeType.Length()!=NULL)
        {
        TUid ret(TUid::Null());
        RFs fs;
        User::LeaveIfError(fs.Connect());
        CleanupClosePushL(fs);
        CFileMan *fm = CFileMan::NewL(fs);
        CleanupStack::PushL(fm);
        TFileName oldfilepath;
        oldfilepath.Copy(iDataFileName);
        
        
        RDEBUG("App Mgmt before copy start");
        TInt maxLength = iDataFileName.Length();
        TChar charvaldot = '.';
        TChar charvalslash = '\\';
        //TFileName oldfilepath;
        TInt pos = iDataFileName.LocateReverse(charvaldot);

        TInt lengthDeleted = maxLength - pos;

        iDataFileName.Delete(pos, lengthDeleted);
        
        if (iMimeType == KSisxMimeType)
            {
            _LIT16(KExt,".sisx");
            iExtn.Append(KExt);
            }
        if(iMimeType==KSisMimeType)
            {
            _LIT16(KExt,".sis");
            iExtn.Append(KExt);
            }
        if(iMimeType==KPipMimeType)
            {
            _LIT16(KExt,".pip");
            iExtn.Append(KExt);
            }
        if(iMimeType==KJadMIMEType)
            {
            _LIT16(KExt,".jad");
            iExtn.Append(KExt);
            }
        if(iMimeType==KJarMIMEType)
            {
            _LIT16(KExt,".jar");
            iExtn.Append(KExt);
            }
        if(iMimeType==KJavaMIMEType)
            {
            _LIT16(KExt,".jar");
            iExtn.Append(KExt);
            }
        iDataFileName.Append(iExtn);//file name with sisx extension
        TFileName newfilepath;
        newfilepath.Copy(iDataFileName);
        User::LeaveIfError(fm->Rename(oldfilepath, newfilepath));
        CleanupStack::PopAndDestroy(fm);
        CleanupStack::PopAndDestroy( &fs);
        //RDEBUG_2(" filename: %S", iDataFileName );
        }
    if (IsSISInstallFile(aMimeType) )
        {
        RFs fs;
        User::LeaveIfError(fs.Connect() );
        CleanupClosePushL(fs);     
        ret = ResolveUidL(fs);
        CleanupStack::PopAndDestroy( &fs);
        }
    RDEBUG8_2("CDeploymentComponentData::SetDataL() UID: (0x%x)", ret.iUid);
    return ret;
    }