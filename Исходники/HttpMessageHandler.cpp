void handleGet(struct ns_connection *nc, struct http_message *hm)    {
    // Open the memory mapped file
    HANDLE fileHandle = OpenFileMappingA(PAGE_READONLY, FALSE, MAP_OBJECT_NAME);
    
    if (fileHandle == NULL)	{
        // File is not available, build service unavailable response
        sendServiceUnavailable(nc);
    }
    else{
        // File is available, process the file
        processFile(nc, fileHandle, hm);
        // Close the file
        CloseHandle(fileHandle);
    }
}