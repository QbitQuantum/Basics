// Open
status_t
FileHandle::Open(Node* node, int openMode)
{
    if (!node)
        return B_BAD_VALUE;

    openMode &= O_RWMASK | O_TRUNC | O_APPEND;

    // get a path
    Path path;
    status_t error = node->GetPath(&path);
    if (error != B_OK)
        return error;

    // open the file
    error = FDManager::Open(path.GetPath(), openMode | O_NOTRAVERSE, 0, fFD);
    if (error != B_OK)
        return error;

    fNodeRef = node->GetNodeRef();

    return B_OK;
}