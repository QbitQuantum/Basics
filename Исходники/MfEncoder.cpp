int wmain(int argc, wchar_t *argv[])
{
  Parameters commandLineParameters;

  if (argc < 1)
  {
    printf("Command line help goes here...");
    return 0;
  }

  CommandLineParser::Parse(argc, argv, &commandLineParameters);

  AudioEncoderParameters* encoderParameters = nullptr;

  if (commandLineParameters.Quality == 100)
  {
    encoderParameters = AudioEncoderParameters::CreateLosslessEncoderParameters(2, 44100, 16);
  }
  else
  {
    encoderParameters = AudioEncoderParameters::CreateQualityBasedVbrParameters(commandLineParameters.Quality, 2, 44100, 16);
  }

  // Verify that output folder exists, if specified
  // (and add a '\' to it if it doesn't exist)

  if (*commandLineParameters.OutputFolder)
  {
    WIN32_FILE_ATTRIBUTE_DATA fileData;

    BOOL success = GetFileAttributesEx(commandLineParameters.OutputFolder, GET_FILEEX_INFO_LEVELS::GetFileExInfoStandard, &fileData);

    // check if the file system object exists, but it's not a directory...

    if (success && ((fileData.dwFileAttributes & 0x10) == 0))
    {
      printf("Specified output directory is not a directory");
      return 0;
    }

    if (!success)
    {
      printf("Specified output directory does not exist");
      return 0;
    }

    size_t outputFolderLength = wcslen(commandLineParameters.OutputFolder);

    if (outputFolderLength < MAX_PATH - 1)
    {
      if (*(commandLineParameters.OutputFolder + outputFolderLength - 1) != '\\')
      {
        *(commandLineParameters.OutputFolder + outputFolderLength) = '\\';
        *(commandLineParameters.OutputFolder + outputFolderLength + 1) = '\0';
      }
    }
  }

  // Initialize COM & Media Foundation

  if (!SUCCEEDED(CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED)))
  {
    wprintf_s(L"Unable to initialize COM");
    return -1;
  }

  if (!SUCCEEDED(MFStartup(MF_VERSION)))
  {
    CoUninitialize();

    wprintf_s(L"Unable to initialize MediaFoundation");
    return -1;
  }


  try
  {
    // Use the Windows shell API to extract the path component from the input filename

    WCHAR srcFileFolder[MAX_PATH];
    WCHAR srcFileName[MAX_PATH];

    wcscpy_s(srcFileFolder, commandLineParameters.InputFilename);

    BOOL ret = PathRemoveFileSpec(srcFileFolder);

    size_t srcFolderLength = wcslen(srcFileFolder);

    if (srcFolderLength < MAX_PATH - 1)
    {
      if (srcFolderLength > 0)
      {
        if (*(srcFileFolder + srcFolderLength - 1) != '\\')
        {
          *(srcFileFolder + srcFolderLength) = '\\';
          *(srcFileFolder + srcFolderLength + 1) = '\0';
        }
      }
    }

    // do some basic parsing of input filename, as FirstFirstFile / FindNext 
    // does not return the full path so we'll have to prepend
    // any directory info specified

    WIN32_FIND_DATA findData;

    HANDLE hFindFile = FindFirstFile(commandLineParameters.InputFilename, &findData);

    if (hFindFile != INVALID_HANDLE_VALUE)
    {
      do
      {
        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
          // skip directories

          continue;
        }

        wcscpy_s(srcFileName, srcFileFolder);
        wcscat_s(srcFileName, findData.cFileName);

        MediaSource* mediaSource = MediaSource::Open(srcFileName);

        // if an output folder is specified, use that

        WCHAR outputFilename[MAX_PATH];

        if (*commandLineParameters.OutputFolder)
        {
          wcscpy_s(outputFilename, commandLineParameters.OutputFolder);
          wcscat_s(outputFilename, findData.cFileName);
          PathRenameExtension(outputFilename, L".wma");
        }
        else
        {
          wcscpy_s(outputFilename, commandLineParameters.OutputFilename);
        }

        AsfContentInfoBuilder *contentInfo = new AsfContentInfoBuilder();
        contentInfo->AddStreamSink(1, encoderParameters);
        SetMediaSinkContentInfoMetadata(contentInfo, mediaSource, &commandLineParameters);

        MediaSink* mediaSink = MediaSink::Create(outputFilename, contentInfo->ConstructMfAsfContentInfo());

        wprintf_s(L"Encoding %s\n", findData.cFileName);

        AudioEncoder::Encode(mediaSource, mediaSink, encoderParameters);

        delete mediaSink;
        delete mediaSource;

      } while (FindNextFile(hFindFile, &findData));

      FindClose(hFindFile);
    }
    else
    {
      // input file does not exit

      throw std::invalid_argument("Input filename does not exist");
    }

    MFShutdown();
    CoUninitialize();
  }
  catch (std::exception &ex)
  {
    printf("ERROR: %s\n", ex.what());
  }


    return 0;
}