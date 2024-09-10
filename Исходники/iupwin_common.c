int iupwinBaseContainerMsgProc(Ihandle* ih, UINT msg, WPARAM wp, LPARAM lp, LRESULT *result)
{
  /* All messages here are sent to the parent Window, 
     but they are useful for child controls.  */

  switch (msg)
  {
  case WM_COMMAND:
    {
      Ihandle* child = winContainerWmCommandGetIhandle(ih, wp, lp);
      if (child)
      {
        IFwmCommand cb = (IFwmCommand)IupGetCallback(child, "_IUPWIN_COMMAND_CB");
        if (cb)
          cb(child, wp, lp);
      }

      break;
    }
  case WM_CTLCOLOREDIT:
  case WM_CTLCOLORLISTBOX:
  case WM_CTLCOLORBTN:
  case WM_CTLCOLORSCROLLBAR:
  case WM_CTLCOLORSTATIC:
    {
      Ihandle* child = iupwinHandleGet((HWND)lp);
      if (child && winCheckParent(child, ih))
      {
        IFctlColor cb = (IFctlColor)IupGetCallback(child, "_IUPWIN_CTLCOLOR_CB");
        if (cb)
          return cb(child, (HDC)wp, result);
      }
      break;
    }
  case WM_DRAWITEM:   /* for OWNERDRAW controls */
    {
      Ihandle *child;
      DRAWITEMSTRUCT *drawitem = (LPDRAWITEMSTRUCT)lp;
      if (!drawitem)
        break;

      if (wp == 0) /* a menu */
        child = iupwinMenuGetItemHandle((HMENU)drawitem->hwndItem, drawitem->itemID);
      else
      {
        child = iupwinHandleGet(drawitem->hwndItem); 
        if (child && !winCheckParent(child, ih))
          child = NULL;
      }

      if (child)
      {
        IFdrawItem cb = (IFdrawItem)IupGetCallback(child, "_IUPWIN_DRAWITEM_CB");
        if (cb) 
        {
          cb(child, (void*)drawitem);
          *result = TRUE;
          return 1;
        }
      }
      break;
    }
  case WM_HSCROLL:
  case WM_VSCROLL:
    {
      Ihandle *child = iupwinHandleGet((HWND)lp);
      if (child && winCheckParent(child, ih))
      {
        IFni cb = (IFni)IupGetCallback(child, "_IUPWIN_CUSTOMSCROLL_CB");
        if (cb)
          cb(child, LOWORD(wp));
      }
      break;
    }
  case WM_NOTIFY:   /* Currently, the following controls support custom draw functionality: 
                       Header, List-view, Rebar, Toolbar, ToolTip, Trackbar, Tree-view.
                       And for Button if using Windows XP Style. */
    {
      Ihandle *child;
      NMHDR* msg_info = (NMHDR*)lp;
      if (!msg_info)
        break;

      child = iupwinHandleGet(msg_info->hwndFrom);
      if (child && winCheckParent(child, ih))
      {
        IFnotify cb = (IFnotify)IupGetCallback(child, "_IUPWIN_NOTIFY_CB");
        if (cb)
        {
          int ret;
          if (cb(child, (void*)msg_info, &ret))
          {
            *result = (LRESULT)ret;
            return 1;
          }
        }
      }

      break;
    }
  case WM_MOUSEWHEEL:
  {
    HWND hChild;
    POINT p;
    p.x = GET_X_LPARAM(lp); p.y = GET_Y_LPARAM(lp);
    ScreenToClient(ih->handle, &p);

    hChild = ChildWindowFromPointEx(ih->handle, p, CWP_SKIPDISABLED|CWP_SKIPINVISIBLE|CWP_SKIPTRANSPARENT);
    if (hChild)
    {
      Ihandle* child = iupwinHandleGet(hChild);
      if (child && IupClassMatch(child, "canvas"))  /* will check of all canvas based control classes */
        SendMessage(child->handle, WM_MOUSEWHEEL, wp, lp);
    }
    break;
  }
  default:
    {
      /* sent to the list parent */
      if (msg == WM_DRAGLISTMSG)
      {
        DRAGLISTINFO* lpDrag = (DRAGLISTINFO*) lp;
        Ihandle *child = iupwinHandleGet(lpDrag->hWnd);
        if (child && winCheckParent(child, ih))
        {
          *result = iupwinListDND(child, lpDrag->uNotification, lpDrag->ptCursor);
          return 1;
        }
      }
      break;
    }
  }

  return iupwinBaseMsgProc(ih, msg, wp, lp, result);
}