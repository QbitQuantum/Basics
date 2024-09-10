DWORD FileGroupDelete(INT32 groupId)
{
    CHAR    *path;
    CHAR    buffer[12];
    DWORD   result;

    ASSERT(groupId != -1);
    TRACE("groupId=%d", groupId);

    // Retrieve group file location
    StringCchPrintfA(buffer, ELEMENT_COUNT(buffer), "%i", groupId);
    path = Io_ConfigGetPath("Locations", "Group_Files", buffer, NULL);
    if (path == NULL) {
        TRACE("Unable to retrieve file location.");
        return ERROR_NOT_ENOUGH_MEMORY;
    }

    // Delete group file and free resources
    if (DeleteFileA(path)) {
        result = ERROR_SUCCESS;
    } else {
        result = GetLastError();
        TRACE("Unable to delete file \"%s\" (error %lu).", path, result);
    }

    Io_Free(path);
    return result;
}