  long MultiFileReader::RefreshTSBufferFile()
  {
    if (m_TSBufferFile.IsFileInvalid())
      return S_FALSE;

    unsigned long bytesRead;
    MultiFileReaderFile *file;

    long result;
    int64_t currentPosition;
    int32_t filesAdded, filesRemoved;
    int32_t filesAdded2, filesRemoved2;
    long Error = 0;
    long Loop = 10;

    Wchar_t* pBuffer = NULL;
    do
    {
      Error = 0;
      currentPosition = -1;
      filesAdded = -1;
      filesRemoved = -1;
      filesAdded2 = -2;
      filesRemoved2 = -2;

      int64_t fileLength = m_TSBufferFile.GetFileSize();

      // Min file length is Header ( int64_t + int32_t + int32_t ) + filelist ( > 0 ) + Footer ( int32_t + int32_t )
      if (fileLength <= (int64_t)(sizeof(currentPosition) + sizeof(filesAdded) + sizeof(filesRemoved) + sizeof(wchar_t) + sizeof(filesAdded2) + sizeof(filesRemoved2)))
      {
        if (m_bDebugOutput)
        {
          XBMC->Log(LOG_DEBUG, "MultiFileReader::RefreshTSBufferFile() TSBufferFile too short");
        }
        return S_FALSE;
      }

      m_TSBufferFile.SetFilePointer(0, FILE_BEGIN);

      uint32_t readLength = sizeof(currentPosition) + sizeof(filesAdded) + sizeof(filesRemoved);
      unsigned char* readBuffer = new unsigned char[readLength];

      result = m_TSBufferFile.Read(readBuffer, readLength, &bytesRead);

      if (!SUCCEEDED(result) || bytesRead != readLength)
        Error |= 0x02;

      if (Error == 0)
      {
        currentPosition = *((int64_t*)(readBuffer + 0));
        filesAdded = *((int32_t*)(readBuffer + sizeof(currentPosition)));
        filesRemoved = *((int32_t*)(readBuffer + sizeof(currentPosition) + sizeof(filesAdded)));
      }

      delete[] readBuffer;

      // If no files added or removed, break the loop !
      if ((m_filesAdded == filesAdded) && (m_filesRemoved == filesRemoved))
        break;

      int64_t remainingLength = fileLength - sizeof(currentPosition) - sizeof(filesAdded) - sizeof(filesRemoved) - sizeof(filesAdded2) - sizeof(filesRemoved2);

      // Above 100kb seems stupid and figure out a problem !!!
      if (remainingLength > 100000)
        Error |= 0x10;

      pBuffer = (Wchar_t*) new char[(unsigned int)remainingLength];

      result = m_TSBufferFile.Read((unsigned char*)pBuffer, (uint32_t)remainingLength, &bytesRead);
      if (!SUCCEEDED(result) || (int64_t)bytesRead != remainingLength)
        Error |= 0x20;

      readLength = sizeof(filesAdded) + sizeof(filesRemoved);

      readBuffer = new unsigned char[readLength];

      result = m_TSBufferFile.Read(readBuffer, readLength, &bytesRead);

      if (!SUCCEEDED(result) || bytesRead != readLength)
        Error |= 0x40;

      if (Error == 0)
      {
        filesAdded2 = *((int32_t*)(readBuffer + 0));
        filesRemoved2 = *((int32_t*)(readBuffer + sizeof(filesAdded2)));
      }

      delete[] readBuffer;

      if ((filesAdded2 != filesAdded) || (filesRemoved2 != filesRemoved))
      {
        Error |= 0x80;

        XBMC->Log(LOG_ERROR, "MultiFileReader has error 0x%x in Loop %d. Try to clear SMB Cache.", Error, 10 - Loop);
        XBMC->Log(LOG_DEBUG, "%s: filesAdded %d, filesAdded2 %d, filesRemoved %d, filesRemoved2 %d.", __FUNCTION__, filesAdded, filesAdded2, filesRemoved, filesRemoved2);

        // try to clear local / remote SMB file cache. This should happen when we close the filehandle
        m_TSBufferFile.CloseFile();
        m_TSBufferFile.OpenFile();
        usleep(5000);
      }

      if (Error)
        delete[] pBuffer;

      Loop--;
    } while (Error && Loop); // If Error is set, try again...until Loop reaches 0.

    if (Loop < 8)
    {
      XBMC->Log(LOG_DEBUG, "MultiFileReader has waited %d times for TSbuffer integrity.", 10 - Loop);

      if (Error)
      {
        XBMC->Log(LOG_ERROR, "MultiFileReader has failed for TSbuffer integrity. Error : %x", Error);
        return E_FAIL;
      }
    }

    if ((m_filesAdded != filesAdded) || (m_filesRemoved != filesRemoved))
    {
      long filesToRemove = filesRemoved - m_filesRemoved;
      long filesToAdd = filesAdded - m_filesAdded;
      long fileID = filesRemoved;
      int64_t nextStartPosition = 0;

      if (m_bDebugOutput)
      {
        XBMC->Log(LOG_DEBUG, "MultiFileReader: Files Added %i, Removed %i\n", filesToAdd, filesToRemove);
      }

      // Removed files that aren't present anymore.
      while ((filesToRemove > 0) && (m_tsFiles.size() > 0))
      {
        MultiFileReaderFile *file = m_tsFiles.at(0);

        if (m_bDebugOutput)
        {
          XBMC->Log(LOG_DEBUG, "MultiFileReader: Removing file %s\n", file->filename.c_str());
        }

        delete file;
        m_tsFiles.erase(m_tsFiles.begin());

        filesToRemove--;
      }


      // Figure out what the start position of the next new file will be
      if (m_tsFiles.size() > 0)
      {
        file = m_tsFiles.back();

        if (filesToAdd > 0)
        {
          // If we're adding files the changes are the one at the back has a partial length
          // so we need update it.
          GetFileLength(file->filename.c_str(), file->length);
        }

        nextStartPosition = file->startPosition + file->length;
      }

      // Get the real path of the buffer file
      char* filename;
      std::string sFilename;
      std::string path;
      size_t pos = std::string::npos;

      m_TSBufferFile.GetFileName(&filename);
      sFilename = filename;
      pos = sFilename.find_last_of('/');
      path = sFilename.substr(0, pos + 1);
      //name3 = filename1.substr(pos+1);

      // Create a list of files in the .tsbuffer file.
      std::vector<std::string> filenames;

      Wchar_t* pwCurrFile = pBuffer;    //Get a pointer to the first wchar filename string in pBuffer
      long length = WcsLen(pwCurrFile);

      //XBMC->Log(LOG_DEBUG, "%s: WcsLen(%d), sizeof(wchar_t) == %d.", __FUNCTION__, length, sizeof(wchar_t));

      while (length > 0)
      {
        // Convert the current filename (wchar to normal char)
        char* wide2normal = new char[length + 1];
        WcsToMbs(wide2normal, pwCurrFile, length);
        wide2normal[length] = '\0';

        //unsigned char* pb = (unsigned char*) wide2normal;
        //for (unsigned long i = 0; i < rc; i++)
        //{
        //  XBMC->Log(LOG_DEBUG, "%s: pBuffer byte[%d] == %x.", __FUNCTION__, i, pb[i]);
        //}

        std::string sCurrFile = wide2normal;
        //XBMC->Log(LOG_DEBUG, "%s: filename %s (%s).", __FUNCTION__, wide2normal, sCurrFile.c_str());
        delete[] wide2normal;

        // Modify filename path here to include the real (local) path
        pos = sCurrFile.find_last_of(92);
        std::string name = sCurrFile.substr(pos + 1);
        if (path.length() > 0 && name.length() > 0)
        {
          // Replace the original path with our local path
          filenames.push_back(path + name);
        }
        else
        {
          // Keep existing path
          filenames.push_back(sCurrFile);
        }

        // Move the wchar buffer pointer to the next wchar string
        pwCurrFile += (length + 1);
        length = WcsLen(pwCurrFile);
      }

      // Go through files
      std::vector<MultiFileReaderFile *>::iterator itFiles = m_tsFiles.begin();
      //std::vector<char*>::iterator itFilenames = filenames.begin();
      std::vector<std::string>::iterator itFilenames = filenames.begin();

      while (itFiles < m_tsFiles.end())
      {
        file = *itFiles;

        itFiles++;
        fileID++;

        if (itFilenames < filenames.end())
        {
          // TODO: Check that the filenames match. ( Ambass : With buffer integrity check, probably no need to do this !)
          itFilenames++;
        }
        else
        {
          XBMC->Log(LOG_DEBUG, "MultiFileReader: Missing files!!\n");
        }
      }

      while (itFilenames < filenames.end())
      {
        std::string pFilename = *itFilenames;

        if (m_bDebugOutput)
        {
          int nextStPos = (int)nextStartPosition;
          XBMC->Log(LOG_DEBUG, "MultiFileReader: Adding file %s (%i)\n", pFilename.c_str(), nextStPos);
        }

        file = new MultiFileReaderFile();
        file->filename = pFilename;
        file->startPosition = nextStartPosition;

        fileID++;
        file->filePositionId = fileID;

        GetFileLength(file->filename.c_str(), file->length);

        m_tsFiles.push_back(file);

        nextStartPosition = file->startPosition + file->length;

        itFilenames++;
      }

      m_filesAdded = filesAdded;
      m_filesRemoved = filesRemoved;

      delete[] pBuffer;
    }

    if (m_tsFiles.size() > 0)
    {
      file = m_tsFiles.front();
      m_startPosition = file->startPosition;
      // Since the buffer file may be re-used when a channel is changed, we
      // want the start position to reflect the position in the file after the last
      // channel change, or the real start position, whichever is larger
      if (m_lastZapPosition > m_startPosition)
      {
        m_startPosition = m_lastZapPosition;
      }

      file = m_tsFiles.back();
      file->length = currentPosition;
      m_endPosition = file->startPosition + currentPosition;

      if (m_bDebugOutput)
      {
        int64_t stPos = m_startPosition;
        int64_t endPos = m_endPosition;
        int64_t curPos = m_currentReadPosition;
        XBMC->Log(LOG_DEBUG, "StartPosition %lli, EndPosition %lli, CurrentPosition %lli\n", stPos, endPos, curPos);
      }
    }
    else
    {
      m_startPosition = 0;
      m_endPosition = 0;
    }

    return S_OK;
  }