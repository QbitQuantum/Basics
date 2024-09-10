void TFuncSpecView::Paint(TDC& dc, bool erase, TRect& rect)
{
  TSwitchMinApp* theApp = TYPESAFE_DOWNCAST(GetApplication(), TSwitchMinApp);
  if (theApp) {
    // Only paint if we're printing and we have something to paint, otherwise do nothing.
    //
    if (theApp->Printing && theApp->Printer && !rect.IsEmpty()) {
      // Use pageSize to get the size of the window to render into.  For a Window it's the client area,
      // for a printer it's the printer DC dimensions and for print preview it's the layout window.
      //
      TSize   pageSize(rect.right - rect.left, rect.bottom - rect.top);

      TPrintDialog::TData& printerData = theApp->Printer->GetSetup();

      // Get area we can draw in
      TRect drawingArea(swdoc->PaintHeader(dc, rect, "", 0, 0, false), rect.BottomRight());

      TEXTMETRIC tm;
      dc.SelectObject(TFont("Arial", -12));
      if (!dc.GetTextMetrics(tm)) {
        dc.SelectObject(TFont("Arial", -12));
        dc.GetTextMetrics(tm);
      }
      int fHeight=tm.tmHeight+tm.tmExternalLeading;

      unsigned long inputs=swdoc->GetSystem()->GetInputs();

      XPosVector xpos;
      uint divider;
      char* data;

      Print_CreateWidths(xpos, divider, dc);
      if (xpos.back().x < rect.Size().cx) {  // put space in structure to stretch across page
        uint spacing=(rect.Size().cx - xpos.back().x)/(xpos.size()+1);
        uint space_inc=spacing;
        for(XPosVector::size_type i=0; i<xpos.size(); i++) {
          if (i==inputs) {  // after inputs section, increase divider
            divider += space_inc;
            space_inc += spacing;
          }
          xpos[i].x += space_inc;
          space_inc += spacing;
        }
      }

      data=new char[xpos.size()];

      unsigned long PagesDown=1+pow(2,inputs)/( (drawingArea.Size().cy/fHeight) - 2);  // 2 lines for header and horz divider
      unsigned long PagesAcross=1+xpos.back().x/drawingArea.Size().cx;
      unsigned long Pages=1+PagesDown*PagesAcross;

      // Compute the number of pages to print.
      //
      printerData.MinPage = 1;
      printerData.MaxPage = Pages;


      int fromPage = printerData.FromPage == -1 ? 1 : printerData.FromPage;
      int toPage = printerData.ToPage == -1 ? 1 : printerData.ToPage;
      int currentPage = fromPage;

      TPoint p;

      dc.SelectObject(TPen(TColor::Black));

      while (currentPage <= toPage) {
        swdoc->PaintHeader(dc, rect, "Specification", currentPage, Pages, true);
        if (currentPage==1) Print_Summary(dc, drawingArea);
        else {
          // Calculate origin of line by page number
            // x
            int col=((currentPage-2) ) % PagesAcross;
            p.x=drawingArea.left - col * drawingArea.Size().cx;
            // y
            int row=floor((currentPage-2)/PagesAcross);
            p.y=drawingArea.top/* - row * drawingArea.Size().cy*/;

          // Calculate starting and ending input states
          CELL_TYPE state, stateEnd;
          state=(row*(drawingArea.Size().cy-fHeight))/fHeight;
          stateEnd=state+(drawingArea.Size().cy-fHeight)/fHeight;
          if (stateEnd >= (pow(2,inputs)-1) ) stateEnd=pow(2,inputs)-1;

          //
          // Draw header and lines

          // Vertical
          if ( ((p.x+divider) > drawingArea.left) && ((p.x+divider)<drawingArea.right) ) {
            dc.MoveTo(p.x+divider, p.y);
            dc.LineTo(p.x+divider, p.y+((stateEnd-state)+3)*fHeight);
          }

          // Labels
          for(XPosVector::size_type i=0; i<xpos.size(); i++)
            dc.TextOut(TPoint(xpos[i].x, p.y), xpos[i].s.c_str());
          p.y += fHeight;

          // Horizontal
          dc.MoveTo(drawingArea.left, p.y + fHeight/2);
          dc.LineTo(p.x+xpos.back().x, p.y + fHeight/2);
          p.y += fHeight;

          //
          // Draw each line
          while(state <= stateEnd) {
            Print_GenerateLine(data, state);
            Print_Line(dc, p, xpos, data);
            p.y += fHeight;
            state++;
          }
        }

        currentPage++;
      }

      delete[] data;
    }
    else {
      // INSERT>> Normal painting code goes here.
      wTabs->InvalidateRect(rect, erase);
    }
  }
}