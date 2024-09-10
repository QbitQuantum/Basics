static void OnPaintComboPopupListItem(WindowControl * Sender, LKSurface& Surface) {

    if (Sender) {

        if (ComboListPopup->ComboPopupDrawListIndex >= 0 &&
                ComboListPopup->ComboPopupDrawListIndex < ComboListPopup->ComboPopupItemCount) {

            // Fill Background with Highlight color if Selected Item
            if (!Sender->HasFocus() && ComboListPopup->ComboPopupItemIndex == ComboListPopup->ComboPopupDrawListIndex) {
                RECT rc = Sender->GetClientRect();
                Surface.FillRect(&rc, LKBrush_Higlighted);
            }

            const int w = Sender->GetWidth();
            const int h = Sender->GetHeight();

            const TCHAR* szText = ComboListPopup->ComboPopupItemList[ComboListPopup->ComboPopupDrawListIndex]->StringValueFormatted;

            Surface.SetBackgroundTransparent();
            Surface.SetTextColor(RGB_BLACK);
            const int xText = 3 * ScreenScale;
            const int yText = (h - Surface.GetTextHeight(szText)) / 2;
            Surface.DrawTextClip(xText, yText, szText, w - ScreenScale * 5);
        }
    }
}