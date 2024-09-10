ZtringList Dir::GetAllFileNames(const Ztring &Dir_Name_, dirlist_t Options)
{
    ZtringList ToReturn;
    Ztring Dir_Name=Dir_Name_;

    #ifdef ZENLIB_USEWX
        int Flags=wxDIR_FILES | wxDIR_DIRS;

        //Search for files
        wxArrayString Liste;
        wxFileName FullPath; FullPath=Dir_Name.c_str();
        //-File
        if (FullPath.FileExists())
        {
            FullPath.Normalize();
            Liste.Add(FullPath.GetFullPath());
        }
        //-Directory
        else if (FullPath.DirExists())
        {
            FullPath.Normalize();
            wxDir::GetAllFiles(FullPath.GetFullPath(), &Liste, Ztring(), Flags);
        }
        //-WildCards
        else
        {
            wxString FileName=FullPath.GetFullName();
            FullPath.SetFullName(Ztring()); //Supress filename
            FullPath.Normalize();
            if (FullPath.DirExists())
                wxDir::GetAllFiles(FullPath.GetPath(), &Liste, FileName, Flags);
        }

        //Compatible array
        ToReturn.reserve(Liste.GetCount());
        for (size_t Pos=0; Pos<Liste.GetCount(); Pos++)
            ToReturn.push_back(Liste[Pos].c_str());
    #else //ZENLIB_USEWX
        #ifdef WINDOWS
            //Is a dir?
            if (Exists(Dir_Name))
                Dir_Name+=_T("\\*");

            //Path
            Ztring Path=FileName::Path_Get(Dir_Name);
            if (Path.empty())
            {
                #ifdef UNICODE
                    #ifndef ZENLIB_NO_WIN9X_SUPPORT
                    if (IsWin9X_Fast())
                    {
                        DWORD Path_Size=GetFullPathNameA(Dir_Name.To_Local().c_str(), 0, NULL, NULL);
                        char* PathTemp=new char[Path_Size+1];
                        if (GetFullPathNameA(Dir_Name.To_Local().c_str(), Path_Size+1, PathTemp, NULL))
                            Path=FileName::Path_Get(PathTemp);
                        delete [] PathTemp; //PathTemp=NULL;
                    }
                    else
                    #endif //ZENLIB_NO_WIN9X_SUPPORT
                    {
                        DWORD Path_Size=GetFullPathName(Dir_Name.c_str(), 0, NULL, NULL);
                        Char* PathTemp=new Char[Path_Size+1];
                        if (GetFullPathNameW(Dir_Name.c_str(), Path_Size+1, PathTemp, NULL))
                            Path=FileName::Path_Get(PathTemp);
                        delete [] PathTemp; //PathTemp=NULL;
                    }
                #else
                    DWORD Path_Size=GetFullPathName(Dir_Name.c_str(), 0, NULL, NULL);
                    Char* PathTemp=new Char[Path_Size+1];
                    if (GetFullPathName(Dir_Name.c_str(), Path_Size+1, PathTemp, NULL))
                        Path=FileName::Path_Get(PathTemp);
                    delete [] PathTemp; //PathTemp=NULL;
                #endif //UNICODE
            }

            #ifdef UNICODE
                WIN32_FIND_DATAW FindFileDataW;
                HANDLE hFind;
                #ifndef ZENLIB_NO_WIN9X_SUPPORT
                WIN32_FIND_DATAA FindFileDataA;
                if (IsWin9X_Fast())
                    hFind=FindFirstFileA(Dir_Name.To_Local().c_str(), &FindFileDataA);
                else
                #endif //ZENLIB_NO_WIN9X_SUPPORT
                    hFind=FindFirstFileW(Dir_Name.c_str(), &FindFileDataW);
            #else
                WIN32_FIND_DATA FindFileData;
                HANDLE hFind=FindFirstFile(Dir_Name.c_str(), &FindFileData);
            #endif //UNICODE

            if (hFind==INVALID_HANDLE_VALUE)
                return ZtringList();

            BOOL ReturnValue;
            do
            {
                #ifdef UNICODE
                    Ztring File_Name;
                    #ifndef ZENLIB_NO_WIN9X_SUPPORT
                    if (IsWin9X_Fast())
                        File_Name=FindFileDataA.cFileName;
                    else
                    #endif //ZENLIB_NO_WIN9X_SUPPORT
                        File_Name=FindFileDataW.cFileName;
                #else
                    Ztring File_Name(FindFileData.cFileName);
                #endif //UNICODE
                if (File_Name!=_T(".") && File_Name!=_T("..")) //Avoid . an ..
                {
                    Ztring File_Name_Complete=Path+_T("\\")+File_Name;
                    if (Exists(File_Name_Complete))
                    {
                        if (Options&Parse_SubDirs)
                            ToReturn+=GetAllFileNames(File_Name_Complete, Options); //A SubDir
                    }
                    else if ((Options&Include_Hidden) || (!File_Name.empty() && File_Name[0]!=_T('.')))
                        ToReturn.push_back(File_Name_Complete); //A file
                }
                #ifdef UNICODE
                    #ifndef ZENLIB_NO_WIN9X_SUPPORT
                    if (IsWin9X_Fast())
                        ReturnValue=FindNextFileA(hFind, &FindFileDataA);
                    else
                    #endif //ZENLIB_NO_WIN9X_SUPPORT
                        ReturnValue=FindNextFileW(hFind, &FindFileDataW);
                #else
                    ReturnValue=FindNextFile(hFind, &FindFileData);
                #endif //UNICODE
            }
            while (ReturnValue);

            FindClose(hFind);
        #else //WINDOWS
            //A file?
            if (File::Exists(Dir_Name))
            {
               ToReturn.push_back(Dir_Name); //TODO
               return ToReturn;
            }

            //A dir?
            if (!Dir::Exists(Dir_Name))
                return ToReturn; //Does not exist

            //open
            #ifdef UNICODE
                DIR* Dir=opendir(Dir_Name.To_Local().c_str());
            #else
                DIR* Dir=opendir(Dir_Name.c_str());
            #endif //UNICODE
            if (Dir)
            {
                //This is a dir
                //Normalizing dir (the / at the end)
                size_t Dir_Pos=Dir_Name.rfind(FileName_PathSeparator);
                if (Dir_Pos==std::string::npos)
                    Dir_Name+=FileName_PathSeparator;
                else if (Dir_Pos+Ztring(FileName_PathSeparator).size()!=Dir_Name.size())
                    Dir_Name+=FileName_PathSeparator;

                struct dirent *DirEnt;
                while((DirEnt=readdir(Dir))!=NULL)
                {
                    //A file
                    Ztring File_Name(DirEnt->d_name);
                    if (File_Name!=_T(".") && File_Name!=_T("..")) //Avoid . an ..
                    {
                        Ztring File_Name_Complete=Dir_Name+File_Name;
                        if (Exists(File_Name_Complete))
                        {
                            if (Options&Parse_SubDirs)
                                ToReturn+=GetAllFileNames(File_Name_Complete, Options); //A SubDir
                        }
                        else if ((Options&Include_Hidden) || (!File_Name.empty() && File_Name[0]!=_T('.')))
                            ToReturn.push_back(File_Name_Complete); //A file
                    }
                }

                //Close it
                closedir(Dir);
            }
            else
            {
                glob_t globbuf;
                if (glob(Dir_Name.To_Local().c_str(), GLOB_NOSORT, NULL, &globbuf)==0)
                {
                    for (int Pos=0; Pos<globbuf.gl_pathc; Pos++)
                        ToReturn.push_back(Ztring().From_Local(globbuf.gl_pathv[Pos]));
                }
            }
        #endif
    #endif //ZENLIB_USEWX

    return ToReturn;
}