void OEditor::UpdateCursor() {
  int i;
  int nls;  // newlines
  int l;
  
//   find the number of newlines
  nls = 0;
  for (i=bufpos; i<=CursorPos; i++) {
    //if (i>0) 
      if (getChar(i) == '\n') {
        nls++;
      }
  }
  cury = nls;
  
  l = buf.lastIndexOf('\n', CursorPos); // search backwards
  DebugInt(l);
  if (l==-1) {
    curx = CursorPos;     // we are on first row
  } else {
    //curx = CursorPos - buf.lastIndexOf('\n', CursorPos) ;
    curx = CursorPos - l;
  }
}