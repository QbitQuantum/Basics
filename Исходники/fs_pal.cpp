void FS_MountVolume( LPCSTR nameSpace, UINT32 serialNumber, UINT32 deviceFlags, BlockStorageDevice* blockStorageDevice )
{
    FileSystemVolume* volume = NULL;
    UINT32 numVolumes = 0;
    FILESYSTEM_DRIVER_INTERFACE* fsDriver = NULL;
    STREAM_DRIVER_INTERFACE* streamDriver = NULL;
    UINT32 i;
    
    if(!nameSpace || !blockStorageDevice)
    {
        return;
    }

    //--//

    // free up any memory taken up by this block storage device in the zombie list
    // so at any given time, we'll only have one set of FileSystemVolume per block 
    // storage device. Here we release (private_free) the memory that was allocated
    // in the previous insertion, later, prior to AddVolume, we'll allocate new memory
    // needed for this insertion.
    FileSystemVolume* current = FileSystemVolumeList::s_zombieVolumeList.FirstValidNode();
    FileSystemVolume* next;
    
    while(current)
    {
        next = current->Next();

        if(!(next && next->Next()))
        {    
            next = NULL;
        }

        // We'll only free the memory of this storage device
        if(current->m_volumeId.blockStorageDevice == blockStorageDevice)
        {
            current->Unlink();

            private_free( current );
        }

        current = next;
    }

    //--//

    /// First we find the FSDriver that will mount the block storage
    for (i = 0; i < g_InstalledFSCount; i++)
    {
        if (g_AvailableFSInterfaces[i].fsDriver && g_AvailableFSInterfaces[i].fsDriver->IsLoadableMedia &&
            g_AvailableFSInterfaces[i].fsDriver->IsLoadableMedia( blockStorageDevice, &numVolumes ))
        {
            fsDriver = g_AvailableFSInterfaces[i].fsDriver;
            streamDriver = g_AvailableFSInterfaces[i].streamDriver;
            break;
        }
    }

    if (!fsDriver)
    {
        numVolumes = 1;
    }

    for (i = 0; i < numVolumes; i++)
    {
        // Allocate the memory for this FileSystemVolume
        volume = (FileSystemVolume*)private_malloc( sizeof(FileSystemVolume) );

        if(!volume) // allocation failed
        {
            return;
        }

        // initialize content to 0
        memset( volume, 0, sizeof(FileSystemVolume) );

        if(!FileSystemVolumeList::AddVolume( volume, nameSpace, serialNumber, deviceFlags,
                                            streamDriver, fsDriver, blockStorageDevice, i, (fsDriver) ? TRUE : FALSE )) // init only when we have a valid fsDriver
        {
            // If for some reason, AddVolume fails, we'll keep trying other volumes
            private_free( volume );
            continue;
        }

        // Now we can notify managed code
        PostManagedEvent( EVENT_STORAGE, EVENT_SUBCATEGORY_MEDIAINSERT, 0, (UINT32)volume );
    }
}