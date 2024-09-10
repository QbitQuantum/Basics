int WINAPI _tWinMain(HINSTANCE hinstExe, HINSTANCE, PTSTR pszCmdLine, int) {

   // Counter fiber execution context
   PVOID pFiberCounter = NULL;   

   // Convert this thread to a fiber.

   /* Converts the current thread into a fiber. 
    * You must convert a thread into a fiber 
	* before you can schedule other fibers. */
   g_FiberInfo.pFiberUI = ConvertThreadToFiber(NULL);

   /* Allocates a fiber local storage (FLS) index. 
    * Any fiber in the process can subsequently use this index 
	* to store and retrieve values that are local to the fiber. */
   g_dwSlot = FlsAlloc(LogMessage);
   FlsSetValue(g_dwSlot, TEXT("UI fiber"));


   // Create the application's UI window.
   g_FiberInfo.hwnd = CreateDialog(hinstExe, MAKEINTRESOURCE(IDD_COUNTER), 
      NULL, Dlg_Proc);

   // Update the window showing which fiber is executing.
   SetDlgItemText(g_FiberInfo.hwnd, IDC_FIBER, TEXT("User interface"));

   // Initially, there is no background processing to be done.
   g_FiberInfo.bps = BPS_DONE;

   // While the UI window still exists...
   BOOL fQuit = FALSE;
   while (!fQuit) {

      // UI messages are higher priority than background processing.
      MSG msg;
	  /* Dispatches incoming sent messages, checks 
	   * the thread message queue for a posted message, 
	   * and retrieves the message (if any exist). 
	   * PM_REMOVE 0x0001 
	   * Messages are removed from the queue after processing by PeekMessage.
	   */
      if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {

         // If a message exists in the queue, process it.
	     /* Determines whether a message is intended 
		  * for the specified dialog box and, 
		  * if it is, processes the message. 
		  * hDlg [in] Type: HWND A handle to the dialog box.
          * lpMsg [in] Type: LPMSG A pointer to an MSG structure 
		  * that contains the message to be checked.
		  */
         if (!IsDialogMessage(g_FiberInfo.hwnd, &msg)) 
		 {
			 /* Translates virtual-key messages into character messages. 
			  * The character messages are posted to the calling thread's message queue, 
			  * to be read the next time the thread calls the GetMessage or PeekMessage function */
             TranslateMessage(&msg);
			 /* Dispatches a message to a window procedure. 
			  * It is typically used to dispatch a message retrieved by the GetMessage function. */
             DispatchMessage(&msg);
         }

         fQuit = (msg.message == WM_QUIT);
         
         if (fQuit)
         {
            // Release FLS slot
            FlsFree(g_dwSlot);

            // The background processing must be stopped. 
            if (pFiberCounter != NULL) { 
               // A recalculation fiber exists; delete it
               DeleteFiber(pFiberCounter); 
               pFiberCounter = NULL; 
            }
         
            // Quit the fiber mode and return to simple thread mode
            ConvertFiberToThread();
            g_FiberInfo.pFiberUI = NULL;
         }
         
      } else {

         // No UI msgs exist; check the state of the background processing.
         switch (g_FiberInfo.bps) {
            case BPS_DONE:
               // No background processing to do; wait for a UI event.
               /* Yields control to other threads when a thread has no other messages 
			    * in its message queue. 
				* The WaitMessage function suspends the thread 
				* and does not return until a new message 
				* is placed in the thread's message queue. */
               WaitMessage();
               break;

            case BPS_STARTOVER:
               // User changed the count; 
               // cancel the current background processing.
               if (pFiberCounter != NULL) { 
                  // A recalculation fiber exists; delete it so that
                  // background processing starts over from the beginning.
                  DeleteFiber(pFiberCounter); 
                  pFiberCounter = NULL; 
               }

               // Convert this thread to a fiber if needed.
               if (g_FiberInfo.pFiberUI == NULL)
                  g_FiberInfo.pFiberUI = ConvertThreadToFiber(NULL);

               LogMessage(TEXT("convert UI thread to fiber..."));

               // Create a new recalc fiber that starts from the beginning.
               pFiberCounter = CreateFiber(0, FiberFunc, &g_FiberInfo);

               // The background processing started; it should continue.
               g_FiberInfo.bps = BPS_CONTINUE;

               // Fall through to BPS_CONTINUE case...

            case BPS_CONTINUE:
               // Allow the background processing to execute...
               SwitchToFiber(pFiberCounter);

               // The background processing has been paused 
               // (because a UI message showed up) or has been 
               // stopped (because the counting has completed).

               // Update the window showing which fiber is executing.
               SetDlgItemText(g_FiberInfo.hwnd, IDC_FIBER, 
                  TEXT("User interface"));

               if (g_FiberInfo.bps == BPS_DONE) { 
                  // The background processing ran to completion. Delete the
                  // fiber so that processing will restart next time.
                  DeleteFiber(pFiberCounter); 
                  pFiberCounter = NULL; 
               
                  // Quit the fiber mode and return to simple thread mode
                  ConvertFiberToThread();
                  g_FiberInfo.pFiberUI = NULL;
               }
               break;
         }  // switch on background processing state

      }  // No UI messages exist
   }  // while the window still exists

   DestroyWindow(g_FiberInfo.hwnd); 

   return(0);  // End the application.
}