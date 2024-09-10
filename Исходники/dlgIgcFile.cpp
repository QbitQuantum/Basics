 void OnPaintIgcFileListItem(WindowControl * Sender, LKSurface& Surface) {
     if (DrawListIndex < FileList.size()) {
         FileList_t::const_iterator ItFileName = FileList.begin();
         std::advance(ItFileName, DrawListIndex);
         int w0 = Sender->GetWidth();
       
         Surface.SetTextColor(RGB_BLACK);
         Surface.DrawTextClip(2 * ScreenScale, 2 * ScreenScale, ItFileName->c_str(), w0 - ScreenScale * 5);
     }
 }