static LRESULT vboxClipboardProcessMsg(PVBOXCLIPBOARDCONTEXT pCtx, HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    AssertPtr(pCtx);

    const PVBOXCLIPBOARDWINCTX pWinCtx = &pCtx->Win;

    LRESULT rc = 0;

    switch (msg)
    {
        case WM_CLIPBOARDUPDATE:
        {
           Log(("WM_CLIPBOARDUPDATE\n"));

           if (GetClipboardOwner() != hwnd)
           {
               /* Clipboard was updated by another application. */
               uint32_t uFormats;
               int vboxrc = VBoxClipboardWinGetFormats(&pCtx->Win, &uFormats);
               if (RT_SUCCESS(vboxrc))
                   vboxrc = VbglR3ClipboardReportFormats(pCtx->u32ClientID, uFormats);
           }
        }
        break;

        case WM_CHANGECBCHAIN:
        {
           if (VBoxClipboardWinIsNewAPI(&pWinCtx->newAPI))
           {
               rc = DefWindowProc(hwnd, msg, wParam, lParam);
               break;
           }

           HWND hWndRemoved = (HWND)wParam;
           HWND hWndNext    = (HWND)lParam;

           LogFlowFunc(("WM_CHANGECBCHAIN: hWndRemoved=%p, hWndNext=%p, hWnd=%p\n", hWndRemoved, hWndNext, pWinCtx->hWnd));

           if (hWndRemoved == pWinCtx->hWndNextInChain)
           {
               /* The window that was next to our in the chain is being removed.
                * Relink to the new next window. */
               pWinCtx->hWndNextInChain = hWndNext;
           }
           else
           {
               if (pWinCtx->hWndNextInChain)
               {
                   /* Pass the message further. */
                   DWORD_PTR dwResult;
                   rc = SendMessageTimeout(pWinCtx->hWndNextInChain, WM_CHANGECBCHAIN, wParam, lParam, 0,
                                           VBOX_CLIPBOARD_CBCHAIN_TIMEOUT_MS, &dwResult);
                   if (!rc)
                       rc = (LRESULT)dwResult;
               }
           }
        }
        break;

        case WM_DRAWCLIPBOARD:
        {
           LogFlowFunc(("WM_DRAWCLIPBOARD, hwnd %p\n", pWinCtx->hWnd));

           if (GetClipboardOwner() != hwnd)
           {
               /* Clipboard was updated by another application. */
               /* WM_DRAWCLIPBOARD always expects a return code of 0, so don't change "rc" here. */
               uint32_t uFormats;
               int vboxrc = VBoxClipboardWinGetFormats(pWinCtx, &uFormats);
               if (RT_SUCCESS(vboxrc))
                   vboxrc = VbglR3ClipboardReportFormats(pCtx->u32ClientID, uFormats);
           }

           if (pWinCtx->hWndNextInChain)
           {
               /* Pass the message to next windows in the clipboard chain. */
               SendMessageTimeout(pWinCtx->hWndNextInChain, msg, wParam, lParam, 0, VBOX_CLIPBOARD_CBCHAIN_TIMEOUT_MS, NULL);
           }
        }
        break;

        case WM_TIMER:
        {
           if (VBoxClipboardWinIsNewAPI(&pWinCtx->newAPI))
               break;

           HWND hViewer = GetClipboardViewer();

           /* Re-register ourselves in the clipboard chain if our last ping
            * timed out or there seems to be no valid chain. */
           if (!hViewer || pWinCtx->oldAPI.fCBChainPingInProcess)
           {
               VBoxClipboardWinRemoveFromCBChain(pWinCtx);
               VBoxClipboardWinAddToCBChain(pWinCtx);
           }

           /* Start a new ping by passing a dummy WM_CHANGECBCHAIN to be
            * processed by ourselves to the chain. */
           pWinCtx->oldAPI.fCBChainPingInProcess = TRUE;

           hViewer = GetClipboardViewer();
           if (hViewer)
               SendMessageCallback(hViewer, WM_CHANGECBCHAIN, (WPARAM)pWinCtx->hWndNextInChain, (LPARAM)pWinCtx->hWndNextInChain,
                                   VBoxClipboardWinChainPingProc, (ULONG_PTR)pWinCtx);
        }
        break;

        case WM_CLOSE:
        {
           /* Do nothing. Ignore the message. */
        }
        break;

        case WM_RENDERFORMAT:
        {
           /* Insert the requested clipboard format data into the clipboard. */
           uint32_t fFormat = VBOX_SHARED_CLIPBOARD_FMT_NONE;

           const UINT cfFormat = (UINT)wParam;
           switch (cfFormat)
           {
              case CF_UNICODETEXT:
                  fFormat = VBOX_SHARED_CLIPBOARD_FMT_UNICODETEXT;
                  break;

              case CF_DIB:
                  fFormat = VBOX_SHARED_CLIPBOARD_FMT_BITMAP;
                  break;

#ifdef VBOX_WITH_SHARED_CLIPBOARD_URI_LIST
              case CF_HDROP:
                  fFormat = VBOX_SHARED_CLIPBOARD_FMT_URI_LIST;
                  break;
#endif
              default:
                  if (cfFormat >= 0xC000) /** @todo r=andy Explain. */
                  {
                      TCHAR szFormatName[256]; /** @todo r=andy Do we need Unicode support here as well? */

                      int cActual = GetClipboardFormatName(cfFormat, szFormatName, sizeof(szFormatName) / sizeof(TCHAR));
                      if (cActual)
                      {
                          if (strcmp(szFormatName, "HTML Format") == 0)
                              fFormat = VBOX_SHARED_CLIPBOARD_FMT_HTML;
                      }
                  }
                  break;
           }

           LogFunc(("WM_RENDERFORMAT: format=%u -> fFormat=0x%x\n", cfFormat, fFormat));

           if (fFormat == VBOX_SHARED_CLIPBOARD_FMT_NONE)
           {
               /* Unsupported clipboard format is requested. */
               LogRel(("Clipboard: Unsupported clipboard format requested (0x%x)\n", fFormat));
               VBoxClipboardWinClear();
           }
#ifdef VBOX_WITH_SHARED_CLIPBOARD_URI_LIST
           else if (fFormat == VBOX_SHARED_CLIPBOARD_FMT_URI_LIST)
           {

           }
#endif
           else
           {
               const uint32_t cbPrealloc = _4K;
               uint32_t cb = 0;

               /* Preallocate a buffer, most of small text transfers will fit into it. */
               HANDLE hMem = GlobalAlloc(GMEM_DDESHARE | GMEM_MOVEABLE, cbPrealloc);
               LogFlowFunc(("Preallocated handle hMem = %p\n", hMem));

               if (hMem)
               {
                   void *pMem = GlobalLock(hMem);
                   LogFlowFunc(("Locked pMem = %p, GlobalSize = %ld\n", pMem, GlobalSize(hMem)));

                   if (pMem)
                   {
                       /* Read the host data to the preallocated buffer. */
                       int vboxrc = VbglR3ClipboardReadData(pCtx->u32ClientID, fFormat, pMem, cbPrealloc, &cb);
                       LogFlowFunc(("VbglR3ClipboardReadData returned with rc = %Rrc\n",  vboxrc));

                       if (RT_SUCCESS(vboxrc))
                       {
                           if (cb == 0)
                           {
                               /* 0 bytes returned means the clipboard is empty.
                                * Deallocate the memory and set hMem to NULL to get to
                                * the clipboard empty code path. */
                               GlobalUnlock(hMem);
                               GlobalFree(hMem);
                               hMem = NULL;
                           }
                           else if (cb > cbPrealloc)
                           {
                               GlobalUnlock(hMem);

                               /* The preallocated buffer is too small, adjust the size. */
                               hMem = GlobalReAlloc(hMem, cb, 0);
                               LogFlowFunc(("Reallocated hMem = %p\n", hMem));

                               if (hMem)
                               {
                                   pMem = GlobalLock(hMem);
                                   LogFlowFunc(("Locked pMem = %p, GlobalSize = %ld\n", pMem, GlobalSize(hMem)));

                                   if (pMem)
                                   {
                                       /* Read the host data to the preallocated buffer. */
                                       uint32_t cbNew = 0;
                                       vboxrc = VbglR3ClipboardReadData(pCtx->u32ClientID, fFormat, pMem, cb, &cbNew);
                                       LogFlowFunc(("VbglR3ClipboardReadData returned with rc = %Rrc, cb = %d, cbNew = %d\n", vboxrc, cb, cbNew));

                                       if (RT_SUCCESS(vboxrc) && cbNew <= cb)
                                       {
                                           cb = cbNew;
                                       }
                                       else
                                       {
                                           GlobalUnlock(hMem);
                                           GlobalFree(hMem);
                                           hMem = NULL;
                                       }
                                   }
                                   else
                                   {
                                       GlobalFree(hMem);
                                       hMem = NULL;
                                   }
                               }
                           }

                           if (hMem)
                           {
                               /* pMem is the address of the data. cb is the size of returned data. */
                               /* Verify the size of returned text, the memory block for clipboard
                                * must have the exact string size.
                                */
                               if (fFormat == VBOX_SHARED_CLIPBOARD_FMT_UNICODETEXT)
                               {
                                   size_t cbActual = 0;
                                   HRESULT hrc = StringCbLengthW((LPWSTR)pMem, cb, &cbActual);
                                   if (FAILED(hrc))
                                   {
                                       /* Discard invalid data. */
                                       GlobalUnlock(hMem);
                                       GlobalFree(hMem);
                                       hMem = NULL;
                                   }
                                   else
                                   {
                                       /* cbActual is the number of bytes, excluding those used
                                        * for the terminating null character.
                                        */
                                       cb = (uint32_t)(cbActual + 2);
                                   }
                               }
                           }

                           if (hMem)
                           {
                               GlobalUnlock(hMem);

                               hMem = GlobalReAlloc(hMem, cb, 0);
                               LogFlowFunc(("Reallocated hMem = %p\n", hMem));

                               if (hMem)
                               {
                                   /* 'hMem' contains the host clipboard data.
                                    * size is 'cb' and format is 'format'. */
                                   HANDLE hClip = SetClipboardData(cfFormat, hMem);
                                   LogFlowFunc(("WM_RENDERFORMAT hClip = %p\n", hClip));

                                   if (hClip)
                                   {
                                       /* The hMem ownership has gone to the system. Finish the processing. */
                                       break;
                                   }

                                   /* Cleanup follows. */
                               }
                           }
                       }
                       if (hMem)
                           GlobalUnlock(hMem);
                   }
                   if (hMem)
                       GlobalFree(hMem);
               }

               /* Something went wrong. */
               VBoxClipboardWinClear();
           }
        }
        break;

        case WM_RENDERALLFORMATS:
        {
           /* Do nothing. The clipboard formats will be unavailable now, because the
            * windows is to be destroyed and therefore the guest side becomes inactive.
            */
           int vboxrc = VBoxClipboardWinOpen(hwnd);
           if (RT_SUCCESS(vboxrc))
           {
               VBoxClipboardWinClear();
               VBoxClipboardWinClose();
           }
        }
        break;

        case VBOX_CLIPBOARD_WM_SET_FORMATS:
        {
           /* Announce available formats. Do not insert data, they will be inserted in WM_RENDER*. */
           VBOXCLIPBOARDFORMATS fFormats = (uint32_t)lParam;

           LogFlowFunc(("VBOX_WM_SHCLPB_SET_FORMATS: fFormats=0x%x\n", fFormats));

           int vboxrc = VBoxClipboardWinOpen(hwnd);
           if (RT_SUCCESS(vboxrc))
           {
               VBoxClipboardWinClear();

               HANDLE hClip = NULL;

               if (fFormats & VBOX_SHARED_CLIPBOARD_FMT_UNICODETEXT)
                   hClip = SetClipboardData(CF_UNICODETEXT, NULL);

               if (fFormats & VBOX_SHARED_CLIPBOARD_FMT_BITMAP)
                   hClip = SetClipboardData(CF_DIB, NULL);

               if (fFormats & VBOX_SHARED_CLIPBOARD_FMT_HTML)
               {
                   UINT format = RegisterClipboardFormat("HTML Format");
                   if (format != 0)
                       hClip = SetClipboardData(format, NULL);
               }

#ifdef VBOX_WITH_SHARED_CLIPBOARD_URI_LIST
               if (fFormats & VBOX_SHARED_CLIPBOARD_FMT_URI_LIST)
                   hClip = SetClipboardData(CF_HDROP, NULL);
#endif

               /** @todo Implement more flexible clipboard precedence for supported formats. */

               if (hClip == NULL)
                   LogRel(("Clipboard: Unsupported format(s) from host (0x%x), ignoring\n", fFormats));

               VBoxClipboardWinClose();

               LogFlowFunc(("VBOX_WM_SHCLPB_SET_FORMATS: hClip=%p, lastErr=%ld\n", hClip, GetLastError()));
           }
        }
        break;

        case VBOX_CLIPBOARD_WM_READ_DATA:
        {
           /* Send data in the specified format to the host. */
           uint32_t u32Formats = (uint32_t)lParam;
           HANDLE hClip = NULL;

           LogFlowFunc(("VBOX_WM_SHCLPB_READ_DATA: u32Formats=0x%x\n", u32Formats));

           int vboxrc = VBoxClipboardWinOpen(hwnd);
           if (RT_SUCCESS(vboxrc))
           {
               if (u32Formats & VBOX_SHARED_CLIPBOARD_FMT_BITMAP)
               {
                   hClip = GetClipboardData(CF_DIB);

                   if (hClip != NULL)
                   {
                       LPVOID lp = GlobalLock(hClip);
                       if (lp != NULL)
                       {
                           vboxrc = VbglR3ClipboardWriteData(pCtx->u32ClientID, VBOX_SHARED_CLIPBOARD_FMT_BITMAP,
                                                             lp, GlobalSize(hClip));
                           GlobalUnlock(hClip);
                       }
                       else
                       {
                           hClip = NULL;
                       }
                   }
               }
               else if (u32Formats & VBOX_SHARED_CLIPBOARD_FMT_UNICODETEXT)
               {
                   hClip = GetClipboardData(CF_UNICODETEXT);

                   if (hClip != NULL)
                   {
                       LPWSTR uniString = (LPWSTR)GlobalLock(hClip);

                       if (uniString != NULL)
                       {
                           vboxrc = VbglR3ClipboardWriteData(pCtx->u32ClientID, VBOX_SHARED_CLIPBOARD_FMT_UNICODETEXT,
                                                             uniString, (lstrlenW(uniString) + 1) * 2);
                           GlobalUnlock(hClip);
                       }
                       else
                       {
                           hClip = NULL;
                       }
                   }
               }
               else if (u32Formats & VBOX_SHARED_CLIPBOARD_FMT_HTML)
               {
                   UINT format = RegisterClipboardFormat("HTML Format");
                   if (format != 0)
                   {
                       hClip = GetClipboardData(format);
                       if (hClip != NULL)
                       {
                           LPVOID lp = GlobalLock(hClip);

                           if (lp != NULL)
                           {
                               vboxrc = VbglR3ClipboardWriteData(pCtx->u32ClientID, VBOX_SHARED_CLIPBOARD_FMT_HTML,
                                                                 lp, GlobalSize(hClip));
                               GlobalUnlock(hClip);
                           }
                           else
                           {
                               hClip = NULL;
                           }
                       }
                   }
               }
#ifdef VBOX_WITH_SHARED_CLIPBOARD_URI_LIST
               else if (u32Formats & VBOX_SHARED_CLIPBOARD_FMT_URI_LIST)
               {
                   hClip = GetClipboardData(CF_HDROP);
                   if (hClip)
                   {
                       HDROP hDrop = (HDROP)GlobalLock(hClip);
                       if (hDrop)
                       {
       /*                    vboxrc = VbglR3ClipboardWriteData(pCtx->u32ClientID, VBOX_SHARED_CLIPBOARD_FMT_URI_LIST,
                                                             );*/
                           GlobalUnlock(hClip);
                       }
                       else
                       {
                           hClip = NULL;
                       }
                   }
               }
#endif
               VBoxClipboardWinClose();
           }

           if (hClip == NULL)
           {
               /* Requested clipboard format is not available, send empty data. */
               VbglR3ClipboardWriteData(pCtx->u32ClientID, 0, NULL, 0);
           }
        }
        break;

        case WM_DESTROY:
        {
           VBoxClipboardWinRemoveFromCBChain(pWinCtx);
           if (pWinCtx->oldAPI.timerRefresh)
               KillTimer(pWinCtx->hWnd, 0);
           /*
            * don't need to call PostQuitMessage cause
            * the VBoxTray already finished a message loop
            */
        }
        break;

        default:
        {
           rc = DefWindowProc(hwnd, msg, wParam, lParam);
        }
        break;
    }

#ifndef DEBUG_andy
    LogFlowFunc(("vboxClipboardProcessMsg returned with rc = %ld\n", rc));
#endif
    return rc;
}