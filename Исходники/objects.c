/*
***************************************************************************
** Store data for addin object.  Returns handle (NULL if error).
***************************************************************************
*/
char* StoreObject(char* name, void* data)
{
    static char *routine = "StoreObject";
    int          status = FAILURE;
    char        *handle = NULL;
    TObject     *node;

    static char buffer[255];

    if (data == NULL)
    {
        JpmcdsErrMsg("%s: No data to store provided.\n", routine);
        goto done;
    }

    if (name == NULL)
    {
        JpmcdsErrMsg("%s: No object name provided.\n", routine);
        goto done;
    }

    if (strlen(name) > 200)
    {
        JpmcdsErrMsg("%s: Object name cannot exceed 200 characters.\n", routine);
        goto done;
    }

    node = FindNode(name);
    if (node == NULL)
    {
        node = NEW(TObject);
        if (node == NULL)
            goto done;

        node->name = strdup(name);
        node->version = 1;
        node->data = data;
        node->next = cache;
        cache = node;
    }
    else
    {
        node->version += 1;
        JpmcdsFreeTCurve((TCurve*)(node->data));
        node->data = data;
    }

    sprintf(buffer, "%s%c%d\0", node->name, SEPARATOR, node->version);
    handle = strdup(buffer);
    if (handle == NULL)
        goto done;

    strcpy(handle, buffer);
    status = SUCCESS;
    
done:
    if (status != SUCCESS)
    {
        JpmcdsErrMsg("%s: Failed!\n", routine);
        FREE(handle);
        handle = NULL;
    }

    return handle;
}