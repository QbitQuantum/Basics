void CSketcherView::OnContextMenu(CWnd* pWnd, CPoint point)
{
   CMenu menu;
   menu.LoadMenu(IDR_CURSOR_MENU);

   // Set check marks if it's the no element menu
   if(m_pSelected == 0)
   {
      // Check color menu items
      COLORREF Color = GetDocument()->GetElementColor();
      menu.CheckMenuItem(ID_COLOR_BLACK,
                     (BLACK==Color?MF_CHECKED:MF_UNCHECKED)|MF_BYCOMMAND);
      menu.CheckMenuItem(ID_COLOR_RED,
                       (RED==Color?MF_CHECKED:MF_UNCHECKED)|MF_BYCOMMAND);
      menu.CheckMenuItem(ID_COLOR_GREEN,
                     (GREEN==Color?MF_CHECKED:MF_UNCHECKED)|MF_BYCOMMAND);
      menu.CheckMenuItem(ID_COLOR_BLUE,
                      (BLUE==Color?MF_CHECKED:MF_UNCHECKED)|MF_BYCOMMAND);

      // Check element menu items
      unsigned int ElementType = GetDocument()->GetElementType();
      menu.CheckMenuItem(ID_ELEMENT_LINE,
                (LINE==ElementType?MF_CHECKED:MF_UNCHECKED)|MF_BYCOMMAND);
      menu.CheckMenuItem(ID_ELEMENT_RECTANGLE,
           (RECTANGLE==ElementType?MF_CHECKED:MF_UNCHECKED)|MF_BYCOMMAND);
      menu.CheckMenuItem(ID_ELEMENT_CIRCLE,
              (CIRCLE==ElementType?MF_CHECKED:MF_UNCHECKED)|MF_BYCOMMAND);
      menu.CheckMenuItem(ID_ELEMENT_CURVE,
               (CURVE==ElementType?MF_CHECKED:MF_UNCHECKED)|MF_BYCOMMAND);
   }
   CMenu* pPopup = menu.GetSubMenu(m_pSelected == 0 ? 1 : 0);
   ASSERT(pPopup != NULL);
   pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
}