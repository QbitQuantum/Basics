/* This remote procedure closes a file on the server. */
short RemoteClose(PCONTEXT_HANDLE_TYPE *pphContext)
{
    FILE_CONTEXT_TYPE *pFileContext;

    printf_s("in RemoteClose\n");

    pFileContext = (FILE_CONTEXT_TYPE *) *pphContext;

    if ( fclose( pFileContext->hFile ) == 0)
        {
        midl_user_free( *pphContext );
        *pphContext = NULL;
        return(0);
        }
    else
        /* Context Rundown routine will attempt to close it again */
        return(-1);
}