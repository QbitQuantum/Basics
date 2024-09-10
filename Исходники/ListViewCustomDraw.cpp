      /// <summary>Custom draws an entire listview item</summary>
      /// <param name="pDraw">Draw/Item data</param>
      /// <param name="stage">Draw stage.</param>
      /// <returns></returns>
      bool  ListViewCustomDraw::onDrawItem(NMLVCUSTOMDRAW* pDraw, Stage stage)
      {
         try
         {
            // DEBUG
            //Console << "onDrawItem item=" << (int)pDraw->nmcd.dwItemSpec << " Stage=" << GetString(stage) << " state=" << pDraw->nmcd.uItemState << ENDL;
      
            // PostPaint: Do nothing
            if (stage == Stage::PostPaint)
               return true;

            // Init
            CDC dc;
            dc.Attach(pDraw->nmcd.hdc);

            // Get item data
            ItemData item((int)pDraw->nmcd.dwItemSpec, 0);
            ListView.GetItemRect(item.Index, item.Rect, LVIR_BOUNDS);
            item.Selected = ListView.GetItemState(item.Index, LVIS_SELECTED) != 0;
            item.Focused  = ListView.GetItemState(item.Index, LVIS_FOCUSED) != 0;

            // Draw background
            bool ListHasFocus = (::GetFocus() == ListView.GetSafeHwnd());
            auto backColour   = (item.Selected ? (ListHasFocus ? ActiveHighlight : InactiveHighlight) : ListView.GetBkColor());
            dc.FillSolidRect(item.Rect, backColour);

            // BugFix: check for header ctrl
            if (!ListView.GetHeaderCtrl())
               throw GenericException(HERE, L"Listview has no header ctrl");

            // Draw sub items:
            for (int count = ListView.GetHeaderCtrl()->GetItemCount(); item.SubItem < count; ++item.SubItem)
            {
               // Get sub-item rectangle
               ListView.GetSubItemRect(item.Index, item.SubItem, LVIR_LABEL, item.Rect);
               item.Rect.DeflateRect(GetSystemMetrics(SM_CXEDGE),0);

               // Reset text colour   [Invert if selected]
               dc.SetTextColor(GetSysColor(item.Selected ? COLOR_HIGHLIGHTTEXT : COLOR_WINDOWTEXT));

               // Allow derived-class to do drawing
               onDrawSubItem(&dc, item);
            }

            // Draw Focus rect:
            if (ListHasFocus && item.Focused)
            {
               ListView.GetItemRect(item.Index, item.Rect, LVIR_BOUNDS);
               dc.DrawFocusRect(item.Rect);
            }

            // Cleanup
            dc.Detach();
            return true;
         }
         catch (ExceptionBase& e) {
            Console.Log(HERE, e);
            return false;
         }
      }