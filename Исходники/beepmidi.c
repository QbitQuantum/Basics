MMRESULT
OpenDevice(
    DeviceInfo** private_data,
    MIDIOPENDESC* open_desc,
    DWORD flags)
{
    NTSTATUS status;
    HANDLE heap;
    HANDLE kernel_device;
    UNICODE_STRING beep_device_name;
    OBJECT_ATTRIBUTES attribs;
    IO_STATUS_BLOCK status_block;

    /* One at a time.. */
    if ( the_device )
    {
        DPRINT("Already allocated\n");
        return MMSYSERR_ALLOCATED;
    }

    /* Make the device name into a unicode string and open it */

    RtlInitUnicodeString(&beep_device_name,
                            L"\\Device\\Beep");

    InitializeObjectAttributes(&attribs,
                                &beep_device_name,
                                0,
                                NULL,
                                NULL);

    status = NtCreateFile(&kernel_device,
                            FILE_READ_DATA | FILE_WRITE_DATA,
                            &attribs,
                            &status_block,
                            NULL,
                            0,
                            FILE_SHARE_READ | FILE_SHARE_WRITE,
                            FILE_OPEN_IF,
                            0,
                            NULL,
                            0);

    if ( ! NT_SUCCESS(status) )
    {
        DPRINT("Could not connect to BEEP device - %d\n", (int) GetLastError());
        return MMSYSERR_ERROR;
    }

    DPRINT("Opened!\n");

    /* Allocate and initialize the device info */

    heap = GetProcessHeap();

    the_device = HeapAlloc(heap, HEAP_ZERO_MEMORY, sizeof(DeviceInfo));

    if ( ! the_device )
    {
        DPRINT("Out of memory\n");
        return MMSYSERR_NOMEM;
    }

    /* Initialize */
    the_device->kernel_device = kernel_device;
    the_device->playing_notes_count = 0;
    the_device->note_list = NULL;
    the_device->thread_handle = 0;
    the_device->terminate_thread = FALSE;
    the_device->running_status = 0;

    // TODO
    the_device->mme_handle = (HDRVR) open_desc->hMidi;
    the_device->callback = open_desc->dwCallback;
    the_device->instance = open_desc->dwInstance;
    the_device->flags = flags;

    /* Store the pointer in the user data */
    *private_data = the_device;

    /* This is threading-related code */
#ifdef CONTINUOUS_NOTES
    the_device->work_available = CreateEvent(NULL, TRUE, FALSE, NULL);

    if ( ! the_device->work_available )
    {
        DPRINT("CreateEvent failed\n");
        HeapFree(heap, 0, the_device);
        return MMSYSERR_NOMEM;
    }

    the_device->thread_handle = CreateThread(NULL,
                                             0,
                                             ProcessPlayingNotes,
                                             (PVOID) the_device,
                                             0,
                                             NULL);

    if ( ! the_device->thread_handle )
    {
        DPRINT("CreateThread failed\n");
        CloseHandle(the_device->work_available);
        HeapFree(heap, 0, the_device);
        return MMSYSERR_NOMEM;
    }
#endif

    /* Now we call the client application to say the device is open */
    DPRINT("Sending MOM_OPEN\n");
    DPRINT("Success? %d\n", (int) CallClient(the_device, MOM_OPEN, 0, 0));

    return MMSYSERR_NOERROR;
}