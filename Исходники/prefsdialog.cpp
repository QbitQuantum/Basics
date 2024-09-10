int wxTreebookExt::ChangeSelection(size_t n) {
   int i = wxTreebook::ChangeSelection(n);
   wxString Temp = GetPageText( n );
   ((wxDialog*)GetParent())->SetTitle( Temp );
   return i;
};