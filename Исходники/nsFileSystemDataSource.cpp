nsresult
FileSystemDataSource::GetVolumeList(nsISimpleEnumerator** aResult)
{
    nsCOMArray<nsIRDFResource> volumes;
    nsCOMPtr<nsIRDFResource> vol;

#ifdef XP_WIN

    int32_t         driveType;
    wchar_t         drive[32];
    int32_t         volNum;

    for (volNum = 0; volNum < 26; volNum++)
    {
        swprintf( drive, L"%c:\\", volNum + (char16_t)'A');

        driveType = GetDriveTypeW(drive);
        if (driveType != DRIVE_UNKNOWN && driveType != DRIVE_NO_ROOT_DIR)
        {
            nsAutoCString url;
            url.AppendPrintf("file:///%c|/", volNum + 'A');
            nsresult rv = mRDFService->GetResource(url, getter_AddRefs(vol));
            if (NS_FAILED(rv))
                return rv;

            volumes.AppendObject(vol);
        }
    }
#endif

#ifdef XP_UNIX
    mRDFService->GetResource(NS_LITERAL_CSTRING("file:///"), getter_AddRefs(vol));
    volumes.AppendObject(vol);
#endif

    return NS_NewArrayEnumerator(aResult, volumes);
}