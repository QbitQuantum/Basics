int WINAPI _tWinMain(HINSTANCE hinstExe, HINSTANCE, PTSTR pszCmdLine, int) 
{
   /* Check if we are not already associated with a job.
    * If this is the case, there is no way to switch to
    * another job.
	*/
   BOOL bInJob = FALSE;
   IsProcessInJob(GetCurrentProcess(), NULL, &bInJob);
   if (bInJob) 
   {
      MessageBox(
		  NULL, 
		  TEXT("Process already in a job"), 
          TEXT(""), 
		  MB_ICONINFORMATION | MB_OK);

      return(-1);
   }

   /* Create the completion port that receives job notifications 
    * Creates an input/output (I/O) completion port 
	* and associates it with a specified file handle, 
	* or creates an I/O completion port that is not 
	* yet associated with a file handle, allowing association at a later time.
    * 
	*  Associating an instance of an opened file handle with an I/O completion 
	*  port allows a process to receive notification of the completion 
	*  of asynchronous I/O operations involving that file handle.
	*
    * FileHandle [in] 
    *   An open file handle or INVALID_HANDLE_VALUE.
    *   The handle must be to an object that supports overlapped I/O.
    *   If a handle is provided, it has to have been opened 
	*   for overlapped I/O completion. 
	*   For example, you must specify the FILE_FLAG_OVERLAPPED flag
	*   when using the CreateFile function to obtain the handle.
	*
    *   If INVALID_HANDLE_VALUE is specified, 
	*   the function creates an I/O completion port without associating it 
	*   with a file handle. In this case, the ExistingCompletionPort parameter 
	*   must be NULL and the CompletionKey parameter is ignored.
    * 
	* ExistingCompletionPort [in, optional] 
    *   A handle to an existing I/O completion port or NULL.
    *   If this parameter is NULL, the function creates a new I/O completion port and, 
	*   if the FileHandle parameter is valid, associates it with the new I/O completion port. 
	*   Otherwise no file handle association occurs. 
	*   The function returns the handle to the new I/O completion port if successful.
	*  
	*  
    */
   g_hIOCP = CreateIoCompletionPort(
	   INVALID_HANDLE_VALUE, 
	   NULL, 
	   0, 
	   0);

   /* Create a thread that waits on the completion port */
   g_hThreadIOCP = chBEGINTHREADEX(
	   NULL, 
	   0, 
	   JobNotify, 
	   NULL, 
	   0, 
	   NULL);

   /* Create the job object */
   g_job.Create(NULL, TEXT("JobLab"));
   g_job.SetEndOfJobInfo(JOB_OBJECT_POST_AT_END_OF_JOB);
   g_job.AssociateCompletionPort(g_hIOCP, COMPKEY_JOBOBJECT);

   DialogBox(hinstExe, MAKEINTRESOURCE(IDD_JOBLAB), NULL, Dlg_Proc);

   /* Post a special key that tells the completion port thread to terminate 
    * Posts an I/O completion packet to an I/O completion port.
	*
	* CompletionPort [in] 
    *   A handle to an I/O completion port to which 
	*   the I/O completion packet is to be posted.
    * 
	* dwNumberOfBytesTransferred [in] 
    *   The value to be returned through the lpNumberOfBytesTransferred 
	*   parameter of the GetQueuedCompletionStatus function.
    *
	* dwCompletionKey [in] 
    *   The value to be returned through the lpCompletionKey parameter 
	*   of the GetQueuedCompletionStatus function.
    * 
	* lpOverlapped [in, optional] 
    *   The value to be returned through the lpOverlapped parameter 
	*   of the GetQueuedCompletionStatus function.
    *
    */
   PostQueuedCompletionStatus(g_hIOCP, 0, COMPKEY_TERMINATE, NULL);

   /* Wait for the completion port thread to terminate */
   WaitForSingleObject(g_hThreadIOCP, INFINITE);
   
   // Clean up everything properly
   CloseHandle(g_hIOCP);
   CloseHandle(g_hThreadIOCP);

   // NOTE: The job is closed when the g_job's destructor is called.
   return(0);
}