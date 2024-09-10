void ParseThread(DWORD TID) 
{
   WAITCHAIN_NODE_INFO chain[WCT_MAX_NODE_COUNT];

   DWORD dwNodesInChain;
   BOOL bDeadlock;
   dwNodesInChain = WCT_MAX_NODE_COUNT;
   DWORD dwNodeCount;

   /* Open thread wait chain session */
   HWCT hWCTSession = OpenThreadWaitChainSession(0, NULL);

   /* Get the chain for the current thread
    * Retrieves the wait chain for the specified thread.
	*
	* WctHandle [in]
    *  A handle to the WCT session created by 
	*  the OpenThreadWaitChainSession function.
	*
	* Context [in, optional]
    *  A pointer to an application-defined context structure 
	*  to be passed to the callback function for an asynchronous session.
	* 
	* Flags [in]
    *  The wait chain retrieval options.
	*  This parameter can be one of more of the following values.
	*           Value	                               Meaning
    *  WCT_OUT_OF_PROC_COM_FLAG	         Enumerates all threads of an out-of-proc MTA 
	*                                    COM server to find the correct thread identifier.
	*  
	*  WCT_OUT_OF_PROC_CS_FLAG	         Retrieves critical-section information from other processes.
	*
	*  WCT_OUT_OF_PROC_FLAG	             Follows the wait chain into other processes. 
	*                                    Otherwise, the function reports the first thread 
	*                                    in a different process but does not retrieve additional information.
	* ThreadId [in]
    *  The identifier of the thread. 
	* 
	* NodeCount [in, out]
    *  On input, a number from 1 to WCT_MAX_NODE_COUNT that specifies 
	*  the number of nodes in the wait chain. 
	*  On return, the number of nodes retrieved. 
	*  If the array cannot contain all the nodes of the wait chain, 
	*  the function fails, GetLastError returns ERROR_MORE_DATA, 
	*  and this parameter receives the number of array elements 
	*  required to contain all the nodes.
    *  For asynchronous sessions, check the value that is passed to the callback function. 
	*  Do not free the variable until the callback function has returned.
    * 
	* NodeInfoArray [out]
    *  An array of WAITCHAIN_NODE_INFO structures that receives the wait chain.
    *  For asynchronous sessions, check the value that is passed 
	*  to the callback function. Do not free the array until the callback function has returned.
	* 
	* IsCycle [out]
    *  If the function detects a deadlock, this variable is set to TRUE; 
	*  otherwise, it is set to FALSE.
    *  For asynchronous sessions, check the value 
	*  that is passed to the callback function. 
	*  Do not free the variable until the callback function has returned.
    */
   if (!GetThreadWaitChain(
	      hWCTSession, 
		  NULL, 
		  WCTP_GETINFO_ALL_FLAGS,
          TID, 
		  &dwNodesInChain, 
		  chain, 
		  &bDeadlock)) 
   {
       dwNodeCount = 0;
	   /* Call onThread callback */
       OnThread(TID, FALSE, 0);
       return;
   }

   // Start the chain processing for the current thread
   dwNodeCount = min(dwNodesInChain, WCT_MAX_NODE_COUNT);
   OnThread(TID, bDeadlock, dwNodesInChain);

   // For each node in the chain, call the virtual method with details
   for 
   (
       DWORD current = 0;
       current < min(dwNodesInChain, WCT_MAX_NODE_COUNT);
       current++
   ) 
   {
        OnChainNodeInfo(TID, current, chain[current]);
   }
}