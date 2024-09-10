idigi_callback_status_t iDigiFileSystem::app_process_file_opendir(idigi_file_path_request_t * const request_data,
                                                        idigi_file_open_response_t * const response_data)
{
    idigi_callback_status_t status = idigi_callback_continue;
    SdFile *dir = new SdFile;

    if (dir == NULL)
    {
    	response_data->error->error_status = idigi_file_out_of_memory;
    }

    *dir = DigiSD.open(request_data->path);

    if (!dir->isOpen() || !dir->isDir())
    {
    	response_data->error->error_status = idigi_file_path_not_found;
    	return status;
    }

    dir->rewind();

    response_data->handle = dir;
    APP_DEBUG("opendir for %s returned %p\n", request_data->path, (void *) dir);

    return status;
}