int wmain(int argc, wchar_t* argv[])
{
    if (argc < 2)
    {
        PrintUsage();
        return 1;
    }

    bool doTrace = false;
    bool generateHash = false;
    bool generateClientManifest = false;
    std::wstring fileName;

    std::wstring outputFileName;
    std::wstring assemblyVersion;
    std::wstring assemblyName;
    std::wstring clientFileName;

    bool batchMode = false;
    std::wstring batchFileName;

    bool directoryMode = false;
    std::wstring directoryPath;

    // Get the command line arguments
    for (int i = 1; i < argc; ++i)
    {
        std::wstring arg = argv[i];
               
		// Hopefully the filename doesn't start with -
		if (arg[0] != L'-')
        {
            fileName = arg;

            TrimQuotes(fileName);
        }
        else if (ToLower(arg.substr(1)) == L"trace")
        {
            doTrace = true;
        }
        else if (ToLower(arg.substr(1, 8)) == L"version")
        {
            assemblyVersion = arg.substr(10);
        }
        else if (ToLower(arg.substr(1, 4)) == L"name")
        {
            assemblyName = arg.substr(6);

            TrimQuotes(assemblyName);
        }
        else if (ToLower(arg.substr(1, 4)) == L"hash")
        {
            generateHash = true;
        }
        else if (ToLower(arg.substr(1, 6)) == L"client")
        {
            generateClientManifest = true;
            clientFileName = arg.substr(8) + L".manifest";
            
            TrimQuotes(clientFileName);
        }
        else if (ToLower(arg.substr(1, 5)) == L"batch")
        {
            batchMode = true;
            batchFileName = arg.substr(7);
        }
        else if (ToLower(arg.substr(1, 3)) == L"dir")
        {
            directoryMode = true;
            directoryPath = arg.substr(5);

            TrimQuotes(directoryPath);
        }
        else
        {
            std::wcout << L"Parameter: " << arg << L" was not recognised" << std::endl;;
        }
    }
        
    // Processing and validation of command line arguments
    if (fileName.empty() && !batchMode && !directoryMode)
    {
        std::wcout << L"No com_dll was given!" << std::endl;
        return 1;
    }

    if (assemblyName.empty() && !batchMode && !directoryMode)
    {
        std::wstring localFile = fileName.substr(fileName.rfind(L'\\') + 1);
        assemblyName = localFile.substr(0, localFile.rfind(L'.')) + L".sxs";
    }
    else if (assemblyName.empty() && directoryMode)
    {
        assemblyName = directoryPath.substr(directoryPath.rfind(L'\\') + 1);
    }
    else if (!assemblyName.empty() && directoryMode)
    {
        std::wcout << L"Directory mode: assemblyName cannot be used!" << std::endl;
        return 1;
    }

    
    if (!assemblyName.empty() && batchMode)
    {
       std::wcout << L"Batch mode: assemblyName cannot be used!" << std::endl;
       return 1;
    }

    std::wstring clientFileNamePath = clientFileName.substr(0, clientFileName.rfind(L'\\') + 1);

    if (clientFileName.empty())
    {
        std::wstring fileNamePath = fileName.substr(0, fileName.rfind(L'\\') + 1);
        outputFileName = fileNamePath + assemblyName + L".manifest";
    }
    else if (directoryMode)
    {
        outputFileName = assemblyName + L".manifest";
    }
    else
    {
        outputFileName = clientFileNamePath + assemblyName + L".manifest";
    }


    if (assemblyVersion.empty() && !batchMode)
    {
        assemblyVersion = L"1.0.0.0";
    }
    else if (!assemblyVersion.empty() && batchMode)
    {
        std::wcout << L"Batch mode: assemblyVersion cannot be used!" << std::endl;
        return 1;
    }

    if (directoryMode && batchMode)
    {
        std::wcout << L"Batch mode and Directory mode cannot be used together!" << std::endl;
        return 1;
    }

    // Generation of the manifest files
    std::vector<DependencyInfo> depencencyList;

    if (batchMode)
    {
        std::wifstream file(batchFileName.c_str());
        std::wstring line;

        while (std::getline(file, line))
        {
            std::wistringstream wis;
            wis.str(line);

            std::getline(wis, fileName, L'|');

            TrimSpaces(fileName);
            TrimQuotes(fileName);

            bool isDirectory = IsDirectory(fileName);
            
            if (!std::getline(wis, assemblyName, L'|') || isDirectory)          
            {
                std::wstring localFile = fileName.substr(fileName.rfind(L'\\') + 1);
                assemblyName = localFile.substr(0, localFile.rfind(L'.'));

                if (!isDirectory)
                {
                    assemblyName += + L".sxs";
                }
            }

            if (!std::getline(wis, assemblyVersion, L'|'))
            {
                assemblyVersion = L"1.0.0.0";
            }

            outputFileName = clientFileNamePath + assemblyName + L".manifest";

            if (isDirectory)
            {
                CreateManifestForDirectory(fileName, doTrace, assemblyName, assemblyVersion, generateHash, outputFileName);
            }
            else
            {
                CreateManifestForModule(fileName, doTrace, assemblyName, assemblyVersion, generateHash, outputFileName);
            }

            depencencyList.push_back(DependencyInfo(assemblyName, assemblyVersion));
        }
    }
    else if (directoryMode)
    {
        CreateManifestForDirectory(directoryPath, doTrace, assemblyName, assemblyVersion, generateHash, outputFileName);

        depencencyList.push_back(DependencyInfo(assemblyName, assemblyVersion));
    }
    else
    {
        CreateManifestForModule(fileName, doTrace, assemblyName, assemblyVersion, generateHash, outputFileName);

        depencencyList.push_back(DependencyInfo(assemblyName, assemblyVersion));
    }

    if (generateClientManifest)
    {
        ManifestWriter::WriteClientManifest(clientFileName, depencencyList);
    }

	return 0;
}