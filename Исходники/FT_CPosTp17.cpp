// ---------------------------------------------------------
// CPosTp17::SetupTestDataL()
//
// (other items were commented in a header).
// ---------------------------------------------------------
//
void CPosTp17::SetupTestDataL()
    {  
    iLog->Put(_L("SetupTestDataL"));
    
    _LIT(KLANDMARK,"z:\\sys\\bin\\eposlandmarks.dll");
    RFs fs;
    User::LeaveIfError(fs.Connect());
    CleanupClosePushL(fs);
    
    CFileMan* fileMan = CFileMan::NewL(fs);
    CleanupStack::PushL(fileMan);
    
    //check if landmark is flashed
     if (BaflUtils::FileExists(fs, KLANDMARK))
        {
         //Landmark is flashed
        User::LeaveIfError(iDllNames.Append(_L("z:\\sys\\bin\\eposlandmarks.dll")));        
        User::LeaveIfError(iDllNames.Append(_L("z:\\sys\\bin\\eposlmsearchlib.dll")));
        User::LeaveIfError(iDllNames.Append(_L("z:\\sys\\bin\\eposlmmultidbsearch.dll")));
        User::LeaveIfError(iDllNames.Append(_L("z:\\sys\\bin\\eposlmlocalsearchprovider.dll")));
        User::LeaveIfError(iDllNames.Append(_L("z:\\sys\\bin\\eposlmlocalaccessprovider.dll"))); 
        User::LeaveIfError(iDllNames.Append(_L("z:\\sys\\bin\\eposlmlocalaccess.dll")));
        User::LeaveIfError(iDllNames.Append(_L("z:\\sys\\bin\\eposlmservlib.dll")));
        User::LeaveIfError(iDllNames.Append(_L("z:\\sys\\bin\\eposlmserver.exe")));
        User::LeaveIfError(iDllNames.Append(_L("z:\\sys\\bin\\eposlmdbreg.dll")));
        User::LeaveIfError(iDllNames.Append(_L("z:\\sys\\bin\\eposlmintservices.dll")));
        User::LeaveIfError(iDllNames.Append(_L("z:\\sys\\bin\\eposlmconverter.dll")));
        User::LeaveIfError(iDllNames.Append(_L("z:\\sys\\bin\\eposlmrecognizer.dll")));
        User::LeaveIfError(iDllNames.Append(_L("z:\\sys\\bin\\eposlmdbmanlib.dll")));
        User::LeaveIfError(iDllNames.Append(_L("z:\\sys\\bin\\eposlmdbmanprov.dll")));
        User::LeaveIfError(iDllNames.Append(_L("z:\\sys\\bin\\eposlmlocaldbmanprovider.dll")));
        }
     else
        {
         //Landmark is not flashed
        User::LeaveIfError(iDllNames.Append(_L("!:\\sys\\bin\\eposlandmarks.dll")));
        User::LeaveIfError(iDllNames.Append(_L("!:\\sys\\bin\\eposlmsearchlib.dll")));
        User::LeaveIfError(iDllNames.Append(_L("!:\\sys\\bin\\eposlmmultidbsearch.dll")));
        User::LeaveIfError(iDllNames.Append(_L("!:\\sys\\bin\\eposlmlocalsearchprovider.dll")));
        User::LeaveIfError(iDllNames.Append(_L("!:\\sys\\bin\\eposlmlocalaccessprovider.dll"))); 
        User::LeaveIfError(iDllNames.Append(_L("!:\\sys\\bin\\eposlmlocalaccess.dll")));
        User::LeaveIfError(iDllNames.Append(_L("!:\\sys\\bin\\eposlmservlib.dll")));
        User::LeaveIfError(iDllNames.Append(_L("!:\\sys\\bin\\eposlmserver.exe")));
        User::LeaveIfError(iDllNames.Append(_L("!:\\sys\\bin\\eposlmdbreg.dll")));
        User::LeaveIfError(iDllNames.Append(_L("!:\\sys\\bin\\eposlmintservices.dll")));
        User::LeaveIfError(iDllNames.Append(_L("!:\\sys\\bin\\eposlmconverter.dll")));
        User::LeaveIfError(iDllNames.Append(_L("!:\\sys\\bin\\eposlmrecognizer.dll")));
        User::LeaveIfError(iDllNames.Append(_L("!:\\sys\\bin\\eposlmdbmanlib.dll")));
        User::LeaveIfError(iDllNames.Append(_L("!:\\sys\\bin\\eposlmdbmanprov.dll")));
        User::LeaveIfError(iDllNames.Append(_L("!:\\sys\\bin\\eposlmlocaldbmanprovider.dll")));
        }

    User::LeaveIfError(iFootprints.Append(9000));  //eposlandmarks.dll (Landmarks Client Library)
    // Note that eposlmmultidbsearch.dll + eposlmsearchlib.dll must not be bigger than 17000
    User::LeaveIfError(iFootprints.Append(8500)); //eposlmsearchlib.dll (Landmarks Search Client Library)
    User::LeaveIfError(iFootprints.Append(8500)); //eposlmmultidbsearch.dll (Landmarks Search Client Library)
    User::LeaveIfError(iFootprints.Append(19000)); //eposlmlocalsearchprovider.dll (Landmarks Local Search Provider)
    // Note that eposlmlocalaccessprovider.dll + eposlmlocalaccess.dll must not be bigger than 23000
    User::LeaveIfError(iFootprints.Append(400));   //eposlmlocalaccessprovider.dll (Landmarks Local Access Provider)
    User::LeaveIfError(iFootprints.Append(23000)); //eposlmlocalaccess.dll (Landmarks Local Access)
    User::LeaveIfError(iFootprints.Append(2000));  //eposlmservlib.dll (Landmarks Server Client Library)
    User::LeaveIfError(iFootprints.Append(26000)); //eposlmserver.exe (Landmarks Server)
    User::LeaveIfError(iFootprints.Append(6000));  //eposlmdbreg.dll (Landmarks Database Registry)
    User::LeaveIfError(iFootprints.Append(23000)); //eposlmintservices.dll (Landmarks Internal Services)
    User::LeaveIfError(iFootprints.Append(22000)); //eposlmconverter,dll (Landmarks Content Format Converter)
    User::LeaveIfError(iFootprints.Append(2000));  //eposlmrecognizer.mdl (Landmarks Content Format Recognizer)
    User::LeaveIfError(iFootprints.Append(3000));  //eposlmdbmanlib.dll (Landmarks DB Management Client)
    User::LeaveIfError(iFootprints.Append(6000));  //eposlmdbmanprov.dll (Landmarks Database Management Provider)
    User::LeaveIfError(iFootprints.Append(5000));  //eposlmlocaldbmanprovider.dll (Landmarks Local Database Management Provider)

    CleanupStack::PopAndDestroy(2, &fs);
    }