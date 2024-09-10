//*********************************************************************************************
CStdString CHDFile::GetLocal(const CURL &url)
{
    CStdString path( url.GetFileName() );

    if( url.GetProtocol().Equals("file", false) )
    {
        // file://drive[:]/path
        // file:///drive:/path
        CStdString host( url.GetHostName() );

        if(host.size() > 0)
        {
            if(host.Right(1) == ":")
                path = host + "/" + path;
            else
                path = host + ":/" + path;
        }
    }

#ifdef TARGET_WINDOWS
    path.Insert(0, "\\\\?\\");
    path.Replace('/', '\\');
#endif

    if (IsAliasShortcut(path))
        TranslateAliasShortcut(path);

    return path;
}