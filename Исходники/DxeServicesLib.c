EFIAPI
GetFileBufferByFilePath (
  IN BOOLEAN                           BootPolicy,
  IN CONST EFI_DEVICE_PATH_PROTOCOL    *FilePath,
  OUT      UINTN                       *FileSize,
  OUT UINT32                           *AuthenticationStatus
  )
{
  EFI_DEVICE_PATH_PROTOCOL          *DevicePathNode;
  EFI_DEVICE_PATH_PROTOCOL          *OrigDevicePathNode;
  EFI_DEVICE_PATH_PROTOCOL          *TempDevicePathNode;
  EFI_HANDLE                        Handle;
  EFI_GUID                          *FvNameGuid;
  EFI_FIRMWARE_VOLUME2_PROTOCOL     *FwVol;
  EFI_SECTION_TYPE                  SectionType;
  UINT8                             *ImageBuffer;
  UINTN                             ImageBufferSize;
  EFI_FV_FILETYPE                   Type;
  EFI_FV_FILE_ATTRIBUTES            Attrib;
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL   *Volume;
  EFI_FILE_HANDLE                   FileHandle;
  EFI_FILE_HANDLE                   LastHandle;
  EFI_FILE_INFO                     *FileInfo;
  UINTN                             FileInfoSize;
  EFI_LOAD_FILE_PROTOCOL            *LoadFile;
  EFI_LOAD_FILE2_PROTOCOL           *LoadFile2;
  EFI_STATUS                        Status;

  //
  // Check input File device path.
  //
  if (FilePath == NULL || FileSize == NULL || AuthenticationStatus == NULL) {
    return NULL;
  }

  //
  // Init local variable
  //
  TempDevicePathNode  = NULL;
  FvNameGuid          = NULL;
  FileInfo            = NULL;
  FileHandle          = NULL;
  ImageBuffer         = NULL;
  ImageBufferSize     = 0;
  *AuthenticationStatus = 0;
  
  //
  // Copy File Device Path
  //
  OrigDevicePathNode = DuplicateDevicePath (FilePath);
  if (OrigDevicePathNode == NULL) {
    return NULL;
  }

  //
  // Check whether this device path support FV2 protocol.
  // Is so, this device path may contain a Image.
  //
  DevicePathNode = OrigDevicePathNode;
  Status = gBS->LocateDevicePath (&gEfiFirmwareVolume2ProtocolGuid, &DevicePathNode, &Handle);
  if (!EFI_ERROR (Status)) {
    //
    // For FwVol File system there is only a single file name that is a GUID.
    //
    FvNameGuid = EfiGetNameGuidFromFwVolDevicePathNode ((CONST MEDIA_FW_VOL_FILEPATH_DEVICE_PATH *) DevicePathNode);
    if (FvNameGuid == NULL) {
      Status = EFI_INVALID_PARAMETER;
    } else {
      //
      // Read image from the firmware file
      //
      Status = gBS->HandleProtocol (Handle, &gEfiFirmwareVolume2ProtocolGuid, (VOID**)&FwVol);
      if (!EFI_ERROR (Status)) {
        SectionType = EFI_SECTION_PE32;
        ImageBuffer = NULL;
        Status = FwVol->ReadSection (
                          FwVol,
                          FvNameGuid,
                          SectionType,
                          0,
                          (VOID **)&ImageBuffer,
                          &ImageBufferSize,
                          AuthenticationStatus
                          );
        if (EFI_ERROR (Status)) {
          //
          // Try a raw file, since a PE32 SECTION does not exist
          //
          if (ImageBuffer != NULL) {
            FreePool (ImageBuffer);
            *AuthenticationStatus = 0;
          }
          ImageBuffer = NULL;
          Status = FwVol->ReadFile (
                            FwVol,
                            FvNameGuid,
                            (VOID **)&ImageBuffer,
                            &ImageBufferSize,
                            &Type,
                            &Attrib,
                            AuthenticationStatus
                            );
        }
      }
    }
    if (!EFI_ERROR (Status)) {
      goto Finish;
    }
  }

  //
  // Attempt to access the file via a file system interface
  //
  DevicePathNode = OrigDevicePathNode;
  Status = gBS->LocateDevicePath (&gEfiSimpleFileSystemProtocolGuid, &DevicePathNode, &Handle);
  if (!EFI_ERROR (Status)) {
    Status = gBS->HandleProtocol (Handle, &gEfiSimpleFileSystemProtocolGuid, (VOID**)&Volume);
    if (!EFI_ERROR (Status)) {
      //
      // Open the Volume to get the File System handle
      //
      Status = Volume->OpenVolume (Volume, &FileHandle);
      if (!EFI_ERROR (Status)) {
        //
        // Duplicate the device path to avoid the access to unaligned device path node.
        // Because the device path consists of one or more FILE PATH MEDIA DEVICE PATH
        // nodes, It assures the fields in device path nodes are 2 byte aligned.
        //
        TempDevicePathNode = DuplicateDevicePath (DevicePathNode);
        if (TempDevicePathNode == NULL) {
          FileHandle->Close (FileHandle);
          //
          // Setting Status to an EFI_ERROR value will cause the rest of
          // the file system support below to be skipped.
          //
          Status = EFI_OUT_OF_RESOURCES;
        }
        //
        // Parse each MEDIA_FILEPATH_DP node. There may be more than one, since the
        // directory information and filename can be seperate. The goal is to inch
        // our way down each device path node and close the previous node
        //
        DevicePathNode = TempDevicePathNode;
        while (!EFI_ERROR (Status) && !IsDevicePathEnd (DevicePathNode)) {
          if (DevicePathType (DevicePathNode) != MEDIA_DEVICE_PATH ||
              DevicePathSubType (DevicePathNode) != MEDIA_FILEPATH_DP) {
            Status = EFI_UNSUPPORTED;
            break;
          }
  
          LastHandle = FileHandle;
          FileHandle = NULL;
  
          Status = LastHandle->Open (
                                LastHandle,
                                &FileHandle,
                                ((FILEPATH_DEVICE_PATH *) DevicePathNode)->PathName,
                                EFI_FILE_MODE_READ,
                                0
                                );
  
          //
          // Close the previous node
          //
          LastHandle->Close (LastHandle);
  
          DevicePathNode = NextDevicePathNode (DevicePathNode);
        }
  
        if (!EFI_ERROR (Status)) {
          //
          // We have found the file. Now we need to read it. Before we can read the file we need to
          // figure out how big the file is.
          //
          FileInfo = NULL;
          FileInfoSize = 0;
          Status = FileHandle->GetInfo (
                                FileHandle,
                                &gEfiFileInfoGuid,
                                &FileInfoSize,
                                FileInfo
                                );
  
          if (Status == EFI_BUFFER_TOO_SMALL) {
            FileInfo = AllocatePool (FileInfoSize);
            if (FileInfo == NULL) {
              Status = EFI_OUT_OF_RESOURCES;
            } else {
              Status = FileHandle->GetInfo (
                                    FileHandle,
                                    &gEfiFileInfoGuid,
                                    &FileInfoSize,
                                    FileInfo
                                    );
            }
          }
          
          if (!EFI_ERROR (Status) && (FileInfo != NULL)) {
            //
            // Allocate space for the file
            //
            ImageBuffer = AllocatePool ((UINTN)FileInfo->FileSize);
            if (ImageBuffer == NULL) {
              Status = EFI_OUT_OF_RESOURCES;
            } else {
              //
              // Read the file into the buffer we allocated
              //
              ImageBufferSize = (UINTN)FileInfo->FileSize;
              Status          = FileHandle->Read (FileHandle, &ImageBufferSize, ImageBuffer);
            }
          }
        }
        //
        // Close the file and Free FileInfo and TempDevicePathNode since we are done
        // 
        if (FileInfo != NULL) {
          FreePool (FileInfo);
        }
        if (FileHandle != NULL) {
          FileHandle->Close (FileHandle);
        }
        if (TempDevicePathNode != NULL) {
          FreePool (TempDevicePathNode);
        }
      }
    }
    if (!EFI_ERROR (Status)) {
      goto Finish;
    }
  }

  //
  // Attempt to access the file via LoadFile2 interface
  //
  if (!BootPolicy) {
    DevicePathNode = OrigDevicePathNode;
    Status = gBS->LocateDevicePath (&gEfiLoadFile2ProtocolGuid, &DevicePathNode, &Handle);
    if (!EFI_ERROR (Status)) {
      Status = gBS->HandleProtocol (Handle, &gEfiLoadFile2ProtocolGuid, (VOID**)&LoadFile2);
      if (!EFI_ERROR (Status)) {
        //
        // Call LoadFile2 with the correct buffer size
        //
        ImageBufferSize = 0;
        ImageBuffer     = NULL;
        Status = LoadFile2->LoadFile (
                             LoadFile2,
                             DevicePathNode,
                             FALSE,
                             &ImageBufferSize,
                             ImageBuffer
                             );
        if (Status == EFI_BUFFER_TOO_SMALL) {
          ImageBuffer = AllocatePool (ImageBufferSize);
          if (ImageBuffer == NULL) {
            Status = EFI_OUT_OF_RESOURCES;
          } else {
            Status = LoadFile2->LoadFile (
                                 LoadFile2,
                                 DevicePathNode,
                                 FALSE,
                                 &ImageBufferSize,
                                 ImageBuffer
                                 );
          }
        }
      }
      if (!EFI_ERROR (Status)) {
        goto Finish;
      }
    }
  }

  //
  // Attempt to access the file via LoadFile interface
  //
  DevicePathNode = OrigDevicePathNode;
  Status = gBS->LocateDevicePath (&gEfiLoadFileProtocolGuid, &DevicePathNode, &Handle);
  if (!EFI_ERROR (Status)) {
    Status = gBS->HandleProtocol (Handle, &gEfiLoadFileProtocolGuid, (VOID**)&LoadFile);
    if (!EFI_ERROR (Status)) {
      //
      // Call LoadFile with the correct buffer size
      //
      ImageBufferSize = 0;
      ImageBuffer     = NULL;
      Status = LoadFile->LoadFile (
                           LoadFile,
                           DevicePathNode,
                           BootPolicy,
                           &ImageBufferSize,
                           ImageBuffer
                           );
      if (Status == EFI_BUFFER_TOO_SMALL) {
        ImageBuffer = AllocatePool (ImageBufferSize);
        if (ImageBuffer == NULL) {
          Status = EFI_OUT_OF_RESOURCES;
        } else {
          Status = LoadFile->LoadFile (
                               LoadFile,
                               DevicePathNode,
                               BootPolicy,
                               &ImageBufferSize,
                               ImageBuffer
                               );
        }
      }
    }
  }

Finish:

  if (EFI_ERROR (Status)) {
    if (ImageBuffer != NULL) {
      FreePool (ImageBuffer);
      ImageBuffer = NULL;
    }
    *FileSize = 0;
  } else {
    *FileSize = ImageBufferSize;
  }

  FreePool (OrigDevicePathNode);

  return ImageBuffer;
}