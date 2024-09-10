/* Do_Association_Synchronous() carries out an instance association operation synchronously, retrieving all results
 * on the same thread.  The results can be retrieved on any thread, but that would be unusual for a 
 * synchronous operation. 
 */
void Do_Association_Synchronous(MI_Session *miSession, _In_z_ const wchar_t *namespaceName, MI_Instance *keyInstance, MI_Boolean keysOnly, _In_opt_z_ MI_Char *associationClass, _In_opt_z_ MI_Char *resultClass, _In_opt_z_ MI_Char *roleProperty, _In_opt_z_ MI_Char *resultRoleProperty)
{
    MI_Result miResult = MI_RESULT_OK;
    MI_Result _miResult;
    MI_Operation miOperation = MI_OPERATION_NULL;
    MI_Boolean moreResults;
    const MI_Char *errorString = NULL;
    const MI_Instance *errorDetails = NULL;
    MI_Uint32 instanceCount = 0;

    /* Note that the identity of the thread needs to be the same as the one the session was created on. */

    /* Note, although this sample does not include the PowerShell callbacks for extended semantics, they are allowed
     * on synchronous operations.  Allowable callbacks are:
     *      MI_OperationCallbacks.writeError
     *      MI_OperationCallbacks.writeMessage
     *      MI_OperationCallbacks.writeProgress
     */

    /* Initiate the associator operation.  Synchronous results are always retrieved through a call MI_Operation_GetInstance(). 
     * All operations must be closed with a call to MI_Operation_Close(), but all results must be processed before that.
     * The operation can be cancelled via MI_Operation_Cancel(), although even then all results must be consumed before the operation
     * is closed. 
     */
    MI_Session_AssociatorInstances(miSession, 0, NULL, namespaceName, keyInstance, associationClass, resultClass, roleProperty, resultRoleProperty, keysOnly, NULL, &miOperation);

    /* Must loop through all results until moreResults == MI_FALSE */
    do
    {
        MI_Instance *miInstance;

        /* Retrieve a single instance result */
        _miResult = MI_Operation_GetInstance(&miOperation, &miInstance, &moreResults, &miResult, &errorString, &errorDetails);
        if (_miResult != MI_RESULT_OK)
        {
            /* If this function returns a failure it means that an invalid parameter was passed in, or the identity of the thread
             * is different from the identity the operation was created with.  Both imply programming error.
             */
            wprintf(L"MI_Operation_GetInstance failed, error = %s\n", MI_Result_To_String(_miResult));
            break;
        }
        if (miInstance)
        {
            /* Dump the instance result */
            wprintf(L"------------------------------------------\n");
            Dump_MI_Instance(miInstance, keysOnly, 0);
            instanceCount++;
        }

    } while (miResult == MI_RESULT_OK && moreResults == MI_TRUE);

    /* moreResults == MI_FALSE, dump the final outcome of the operation */
    wprintf(L"------------------------------------------\n");
    if (miResult != MI_RESULT_OK)
    {
        wprintf(L"Operation failed, MI_Result=%s, errorString=%s, errorDetails=\n", MI_Result_To_String(miResult), errorString);
        Dump_MI_Instance(errorDetails, MI_FALSE, 0);
    }
    else
    {
        wprintf(L"Operation succeeded, number of instances=%u\n", instanceCount);
    }
    wprintf(L"------------------------------------------\n");

    /* All operations must be closed.  If an operation is not closed the owning session will hang until the operations
     * are closed fully.  MI_Operation_Close will cancel an operation if it is still running, however results must be
     * consumed before the close can complete fully.  
     * For synchronous operations the MI_Operation_Close() method is synchronous until the final result has been consumed 
     * (moreResults == MI_FALSE).
     */
    _miResult = MI_Operation_Close(&miOperation);
    if (_miResult != MI_RESULT_OK)
    {
        /* This API is likely to fail with invalid parameter, out of memory errors or access denied.
         * When an out of memory error happens, the operation will shut down as best it can.
         * Invalid parameter means a programming error happened.
         * Access denied means the security context while calling into the Close() is different from
         * when the operation was created.  This will be a programming error and could happen if closing 
         * from a different thread and forgetting to impersonate.
         */
        wprintf(L"MI_Operation_Close failed, error %s\n", MI_Result_To_String(_miResult));
    }
}