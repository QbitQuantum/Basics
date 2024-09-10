std::vector<FatxDrive*> FatxDriveDetection::GetAllFatxDrives()
{
    std::vector<std::wstring> logicalDrivePaths = getLogicalDrives();
    std::vector<FatxDrive*> drives;

    std::vector<DeviceIO*> devices = getPhysicalDisks();

    for (size_t i = 0; i < devices.size(); i++)
    {
        if (devices.at(i)->Length() > HddOffsets::Data)
        {
            devices.at(i)->SetPosition(HddOffsets::Data);
            if (devices.at(i)->ReadDword() == FATX_MAGIC)
            {
                FatxDrive *drive = new FatxDrive(static_cast<BaseIO*>(devices.at(i)), FatxHarddrive);
                drives.push_back(drive);
            }
            else
                devices.at(i)->Close();
        }
    }

    std::vector<std::string> dataFiles;
    for (size_t i = 0; i < logicalDrivePaths.size(); i++)
    {
        // clear data files from the previous drive
        dataFiles.clear();

        std::string directory;
        directory.assign(logicalDrivePaths.at(i).begin(), logicalDrivePaths.at(i).end());


#ifdef _WIN32
        WIN32_FIND_DATA fi;

        HANDLE h = FindFirstFile((logicalDrivePaths.at(i) + L"\\Data*").c_str(), &fi);
        if (h != INVALID_HANDLE_VALUE)
        {
            do
            {
                char path[9];
                wcstombs(path, fi.cFileName, wcslen(fi.cFileName) + 1);
                dataFiles.push_back(directory + "\\" + std::string(path));
            }
            while (FindNextFile(h, &fi));

            FindClose(h);

            if (dataFiles.size() >= 3)
            {
                // make sure the data files are loaded in the right order
                std::sort(dataFiles.begin(), dataFiles.end());
                MultiFileIO *io = new MultiFileIO(dataFiles);
                FatxDrive *usbDrive = new FatxDrive(io, FatxFlashDrive);
                drives.push_back(usbDrive);
            }
        }
#else
        DIR *dir = NULL;
        dirent *ent = NULL;
        dir = opendir(directory.c_str());
        if (dir != NULL)
        {
            // search for valid data files
            while ((ent = readdir(dir)) != NULL)
            {
                // the disks start with 'data'
                if (std::string(ent->d_name).substr(0, 4) == "Data")
                    dataFiles.push_back(directory + std::string(ent->d_name));
            }

            if (dataFiles.size() >= 3)
            {
                // make sure the data files are loaded in the right order
                std::sort(dataFiles.begin(), dataFiles.end());
                MultiFileIO *io = new MultiFileIO(dataFiles);
                FatxDrive *usbDrive = new FatxDrive(io, FatxFlashDrive);
                drives.push_back(usbDrive);
            }
        }
#endif
    }

    return drives;
}