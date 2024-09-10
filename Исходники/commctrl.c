/***********************************************************************
 * COMCTL32_SubclassProc (internal)
 *
 * Window procedure for all subclassed windows. 
 * Saves the current subclassing stack position to support nested messages
 */
static LRESULT WINAPI COMCTL32_SubclassProc (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
   LPSUBCLASS_INFO stack;
   LPSUBCLASSPROCS proc;
   LRESULT ret;
    
   TRACE ("(%p, 0x%08x, 0x%08lx, 0x%08lx)\n", hWnd, uMsg, wParam, lParam);

   stack = GetPropW (hWnd, COMCTL32_wSubclass);
   if (!stack) {
      ERR ("Our sub classing stack got erased for %p!! Nothing we can do\n", hWnd);
      return 0;
   }
    
   /* Save our old stackpos to properly handle nested messages */
   proc = stack->stackpos;
   stack->stackpos = stack->SubclassProcs;
   stack->running++;
   ret = DefSubclassProc(hWnd, uMsg, wParam, lParam);
   stack->running--;
   stack->stackpos = proc;
    
   if (!stack->SubclassProcs && !stack->running) {
      TRACE("Last Subclass removed, cleaning up\n");
      /* clean up our heap and reset the original window procedure */
      if (IsWindowUnicode (hWnd))
         SetWindowLongPtrW (hWnd, GWLP_WNDPROC, (DWORD_PTR)stack->origproc);
      else
         SetWindowLongPtrA (hWnd, GWLP_WNDPROC, (DWORD_PTR)stack->origproc);
      Free (stack);
      RemovePropW( hWnd, COMCTL32_wSubclass );
   }
   return ret;
}