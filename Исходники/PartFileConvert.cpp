ConvStatus CPartFileConvert::performConvertToeMule(const CPath& fileName)
{
    wxString filepartindex;

    CPath folder	= fileName.GetPath();
    CPath partfile	= fileName.GetFullName();
    CPath newfilename;

    CDirIterator finder(folder);

    Notify_ConvertUpdateProgressFull(0, _("Reading temp folder"), s_pfconverting->folder.GetPrintable());

    filepartindex = partfile.RemoveAllExt().GetRaw();

    Notify_ConvertUpdateProgress(4, _("Retrieving basic information from download info file"));

    CPartFile* file = new CPartFile();
    s_pfconverting->partmettype = file->LoadPartFile(folder, partfile, false, true);

    switch (s_pfconverting->partmettype) {
    case PMT_UNKNOWN:
    case PMT_BADFORMAT:
        delete file;
        return CONV_BADFORMAT;
    }

    CPath oldfile = folder.JoinPaths(partfile.RemoveExt());

    {
        wxMutexLocker lock(s_mutex);
        s_pfconverting->size = file->GetFileSize();
        s_pfconverting->filename = file->GetFileName();
        s_pfconverting->filehash = file->GetFileHash().Encode();
    }

    Notify_ConvertUpdateJobInfo(s_pfconverting);

    if (theApp->downloadqueue->GetFileByID(file->GetFileHash())) {
        delete file;
        return CONV_ALREADYEXISTS;
    }

    if (s_pfconverting->partmettype == PMT_SPLITTED) {
        unsigned fileindex;
        char *ba = new char [PARTSIZE];

        try {
            CFile inputfile;

            // just count
            unsigned maxindex = 0;
            unsigned partfilecount = 0;
            CPath filePath = finder.GetFirstFile(CDirIterator::File, filepartindex + wxT(".*.part"));
            while (filePath.IsOk()) {
                long l;
                ++partfilecount;
                filePath.GetFullName().RemoveExt().GetExt().ToLong(&l);
                fileindex = (unsigned)l;
                filePath = finder.GetNextFile();
                if (fileindex > maxindex) maxindex = fileindex;
            }
            float stepperpart;
            {
                wxMutexLocker lock(s_mutex);
                if (partfilecount > 0) {
                    stepperpart = (80.0f / partfilecount);
                    if (maxindex * PARTSIZE <= s_pfconverting->size) {
                        s_pfconverting->spaceneeded = maxindex * PARTSIZE;
                    } else {
                        s_pfconverting->spaceneeded = s_pfconverting->size;
                    }
                } else {
                    stepperpart = 80.0f;
                    s_pfconverting->spaceneeded = 0;
                }
            }

            Notify_ConvertUpdateJobInfo(s_pfconverting);

            sint64 freespace = CPath::GetFreeSpaceAt(thePrefs::GetTempDir());
            if (freespace != wxInvalidOffset) {
                if (static_cast<uint64>(freespace) < maxindex * PARTSIZE) {
                    delete file;
                    delete [] ba;
                    return CONV_OUTOFDISKSPACE;
                }
            }

            // create new partmetfile, and remember the new name
            file->CreatePartFile();
            newfilename = file->GetFullName();

            Notify_ConvertUpdateProgress(8, _("Creating destination file"));

            file->m_hpartfile.SetLength( s_pfconverting->spaceneeded );

            unsigned curindex = 0;
            CPath filename = finder.GetFirstFile(CDirIterator::File, filepartindex + wxT(".*.part"));
            while (filename.IsOk()) {
                // stats
                ++curindex;

                Notify_ConvertUpdateProgress(10 + (curindex * stepperpart), CFormat(_("Loading data from old download file (%u of %u)")) % curindex % partfilecount);

                long l;
                filename.GetFullName().RemoveExt().GetExt().ToLong(&l);
                fileindex = (unsigned)l;
                if (fileindex == 0) {
                    filename = finder.GetNextFile();
                    continue;
                }

                uint32 chunkstart = (fileindex - 1) * PARTSIZE;

                // open, read data of the part-part-file into buffer, close file
                inputfile.Open(filename, CFile::read);
                uint64 toReadWrite = std::min<uint64>(PARTSIZE, inputfile.GetLength());
                inputfile.Read(ba, toReadWrite);
                inputfile.Close();

                Notify_ConvertUpdateProgress(10 + (curindex * stepperpart), CFormat(_("Saving data block into new single download file (%u of %u)")) % curindex % partfilecount);

                // write the buffered data
                file->m_hpartfile.WriteAt(ba, chunkstart, toReadWrite);

                filename = finder.GetNextFile();
            }
            delete[] ba;
        } catch (const CSafeIOException& e) {
            AddDebugLogLineC(logPfConvert, wxT("IO error while converting partfiles: ") + e.what());

            delete[] ba;
            file->Delete();
            return CONV_IOERROR;
        }

        file->m_hpartfile.Close();
    }
    // import an external common format partdownload
    else //if (pfconverting->partmettype==PMT_DEFAULTOLD || pfconverting->partmettype==PMT_NEWOLD || Shareaza  )
    {
        if (!s_pfconverting->removeSource) {
            wxMutexLocker lock(s_mutex);
            s_pfconverting->spaceneeded = oldfile.GetFileSize();
        }

        Notify_ConvertUpdateJobInfo(s_pfconverting);

        sint64 freespace = CPath::GetFreeSpaceAt(thePrefs::GetTempDir());
        if (freespace == wxInvalidOffset) {
            delete file;
            return CONV_IOERROR;
        } else if (freespace < s_pfconverting->spaceneeded) {
            delete file;
            return CONV_OUTOFDISKSPACE;
        }

        file->CreatePartFile();
        newfilename = file->GetFullName();

        file->m_hpartfile.Close();

        bool ret = false;

        Notify_ConvertUpdateProgress(92, _("Copy"));

        CPath::RemoveFile(newfilename.RemoveExt());
        if (!oldfile.FileExists()) {
            // data file does not exist. well, then create a 0 byte big one
            CFile datafile;
            ret = datafile.Create(newfilename.RemoveExt());
        } else if (s_pfconverting->removeSource) {
            ret = CPath::RenameFile(oldfile, newfilename.RemoveExt());
        } else {
            ret = CPath::CloneFile(oldfile, newfilename.RemoveExt(), false);
        }
        if (!ret) {
            file->Delete();
            //delete file;
            return CONV_FAILED;
        }

    }

    Notify_ConvertUpdateProgress(94, _("Retrieving source downloadfile information"));

    CPath::RemoveFile(newfilename);
    if (s_pfconverting->removeSource) {
        CPath::RenameFile(folder.JoinPaths(partfile), newfilename);
    } else {
        CPath::CloneFile(folder.JoinPaths(partfile), newfilename, false);
    }

    file->m_hashlist.clear();

    if (!file->LoadPartFile(thePrefs::GetTempDir(), file->GetPartMetFileName(), false)) {
        //delete file;
        file->Delete();
        return CONV_BADFORMAT;
    }

    if (s_pfconverting->partmettype == PMT_NEWOLD || s_pfconverting->partmettype == PMT_SPLITTED) {
        file->SetCompletedSize(file->transferred);
        file->m_iGainDueToCompression = 0;
        file->m_iLostDueToCorruption = 0;
    }

    Notify_ConvertUpdateProgress(100, _("Adding download and saving new partfile"));

    theApp->downloadqueue->AddDownload(file, thePrefs::AddNewFilesPaused(), 0);
    file->SavePartFile();

    if (file->GetStatus(true) == PS_READY) {
        theApp->sharedfiles->SafeAddKFile(file); // part files are always shared files
    }

    if (s_pfconverting->removeSource) {
        CPath oldFile = finder.GetFirstFile(CDirIterator::File, filepartindex + wxT(".*"));
        while (oldFile.IsOk()) {
            CPath::RemoveFile(folder.JoinPaths(oldFile));
            oldFile = finder.GetNextFile();
        }

        if (s_pfconverting->partmettype == PMT_SPLITTED) {
            CPath::RemoveDir(folder);
        }
    }

    return CONV_OK;
}