long WINDOW::Export()
  {
  OpWndItemD*             wi;
  int                     i;
  WNDITEM_DATA*           wid;
  WINDOWRUNTIME*          wr;
  HBRUSH                  hbr;
  HBITMAP                 hbmp;
  char                  	szTitle[I_TITLE_LENGTH+1];

  wr = new WINDOWRUNTIME(1, TRUE);  //This class needs to be created so the shape library name stuff will work

  AUpsfExportField(g_szUpsf_version, 0L, AUPSF_NATV_INT, AUPSF_UNIV_INTEGER, &m_version, sizeof(int));
	GetTitle(szTitle, I_TITLE_LENGTH);
  AUpsfExportField(g_szUpsf_title, 0L, AUPSF_NATV_STRING, AUPSF_UNIV_TEXT, szTitle, (LONG)lstrlen(szTitle) );

  // The pieces of the window style --------
  ExportBool(g_szUpsf_titlebar,    0L, HasTitleBar() );
  ExportBool(g_szUpsf_sysmenu,     0L, HasSysMenu() );
  ExportBool(g_szUpsf_maxbutton,   0L, HasMaxButton() );
  ExportBool(g_szUpsf_minbutton,   0L, HasMinButton() );
  ExportBool(g_szUpsf_horzscroll,  0L, HasHorzScroll() );
  ExportBool(g_szUpsf_vertscroll,  0L, HasVertScroll() );
  ExportBool(g_szUpsf_resize,      0L, HasResizeFrame() );
  ExportBool(g_szUpsf_dialogframe, 0L, HasDialogFrame() );
  ExportBool(g_szUpsf_modal,       0L, IsModal() );
  ExportBool(g_szUpsf_ontop,       0L, IsPopup() );
  ExportBool(g_szUpsf_initvisible, 0L, IsInitVisible() );
  ExportBool(g_szUpsf_drawsmooth,  0L, DrawsSmooth() );
  ExportBool(g_szUpsf_closeonexit, 0L, QuitsOnClose() );

  ExportLogicalRect(m_oiSelf, g_szUpsf_initrect, 0L, &m_rclInitialClient);

  ExportBool(g_szUpsf_limitsize,  0L, m_bLimitMaxSize);
  ExportLogicalPoint(m_oiSelf, g_szUpsf_maxsize, 0L, &m_ptlMaxSize);
  ExportLogicalPoint(m_oiSelf, g_szUpsf_minsize, 0L, &m_ptlMinSize);
  ExportLogicalPoint(m_oiSelf, g_szUpsf_scrollsize, 0L, &m_ptlScrollSize);

  AUpsfExportField(g_szUpsf_menuid, 0L, AUPSF_NATV_OBJECTREF, AUPSF_UNIV_OBJECTREF, &m_oiMenu, sizeof(OBJECTID) );
  AUpsfExportField(g_szUpsf_nextsignal, 0L, AUPSF_NATV_LONG, AUPSF_UNIV_NUMBER, &m_uidNext, sizeof(long) );

  // export the window background information
  hbmp = CreateBitmap(8, 8, 1, 1, m_aPattern);
  hbr  = CreatePatternBrush(hbmp);
  ExportBrush(g_szUpsf_bg_pattern, 0, hbr);
  DeleteObject(hbmp);
  DeleteObject(hbr);
  ExportColor(g_szUpsf_bg_fgcolor, 0, (m_clrForeground == I_WINDOW_FOREGROUND) ? GetSysColor(COLOR_WINDOWTEXT) : m_clrForeground);
  ExportColor(g_szUpsf_bg_bgcolor, 0, (m_clrBackground == I_WINDOW_BACKGROUND) ? GetSysColor(COLOR_WINDOW) : m_clrBackground);
  ExportBool(g_szUpsf_bg_fgdefault, 0, m_clrForeground == I_WINDOW_FOREGROUND);
  ExportBool(g_szUpsf_bg_bgdefault, 0, m_clrBackground == I_WINDOW_BACKGROUND);

  //Now, export the window items..
  m_nItems = (int)( AObjGetDataCount(m_oiSelf) - I_DATA_ITEMS_OFFSET);

  for (i=0; i<m_nItems; i++)
    {
    wid = LockItemData(m_oiSelf, i);
    I_VERIFY_POINTER(wid, continue);

    wi = wid->CreateVI(m_oiSelf, GetItemDataSize(m_oiSelf, i), i);
    I_VERIFY_POINTER(wi, continue);

    if(AUpsfCreateScope(g_szUpsf_item_scope, i)==AUPSF_NOERROR)
      {
      if(WINDOWAPI::IsItemShape(wi) || WINDOWAPI::IsItemGroup(wi))
        {
        AUpsfExportField(g_szUpsf_item_id, 0L, AUPSF_NATV_OBJECTREF, AUPSF_UNIV_OBJECTREF, &m_oiSelf, sizeof(OBJECTID) );
        ExportBool(g_szUpsf_item_shape, 0L, WINDOWAPI::IsItemShape(wi));
        ExportBool(g_szUpsf_item_group, 0L, WINDOWAPI::IsItemGroup(wi));
        ExportLong(g_szUpsf_item_typeid, 0L, (long)wi->Type());
        }
      else
        AUpsfExportField(g_szUpsf_item_id, 0L, AUPSF_NATV_OBJECTREF, AUPSF_UNIV_OBJECTREF, &wi->m_oiObject, sizeof(OBJECTID) );

      ExportLogicalRect(m_oiSelf, g_szUpsf_item_rect, 0L, &wi->m_rcItem);
      ExportBool(g_szUpsf_item_visible, 0L, WINDOWAPI::IsItemVisible(wi) );
      ExportBool(g_szUpsf_item_tabstop, 0L, WINDOWAPI::IsItemTabstop(wi) );
      ExportBool(g_szUpsf_item_groupstop, 0L, WINDOWAPI::IsItemGroupstop(wi) );
      ExportBool(g_szUpsf_item_locked, 0L, WINDOWAPI::IsItemLocked(wi) );
      ExportShort(g_szUpsf_item_growsflag, 0L, wi->m_grow);
      AUpsfExportField(g_szUpsf_item_signalid, 0L, AUPSF_NATV_LONG, AUPSF_UNIV_NUMBER, &wi->m_uidItem, sizeof(long) );

      if(AUpsfCreateScope(g_szUpsf_item_extrascope, 0)==AUPSF_NOERROR)
        {
        if(WINDOWAPI::IsItemShape(wi) || WINDOWAPI::IsItemGroup(wi))
          {
          AObjMessage msg = {(long)wi, 0L, 0L, 0L, ""};
          if((wr->GetShapeAdmin(wi->Type()))(OSHP_QUERYVERSIONANDID, &msg) == A_OK)
            {
            ExportShort(g_szUpsf_shape_version, 0, (short)msg.message2);
            ExportShort(g_szUpsf_shape_type, 0, (short)msg.message3);
            }
          }
        AUpsfExportField(g_szUpsf_shape_dll, 0L, AUPSF_NATV_STRING, AUPSF_UNIV_STRING, wid->m_szShapeDll, strlen(wid->m_szShapeDll));
        wi->ExportExtraData();
        AUpsfCloseScope(); //extra data scope
        }

      AUpsfCloseScope(); //Item scope
      }

    wi->Destroy();
    UnlockItemData(m_oiSelf, i);
    }

  delete wr;
  return A_OK;
  }