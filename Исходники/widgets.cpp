long MyText::onTextCursor(FXObject*o, FXSelector sel, void*p)
{
  if (hasFocus()||(p==this)) {
    static FXint oldpos=0;
    FXint newpos=getCursorPos();
    if (oldpos!=newpos) {
      ClearCursor(oldpos);
      oldpos=newpos;
    }
    FXDCWindow dc(this);
    paintCursor(dc);
    getApp()->addTimeout(this,ID_TEXT_CURSOR,ONE_SECOND/30);
  } else {
    getApp()->addTimeout(this,ID_TEXT_CURSOR,ONE_SECOND);
  }
  return 1;
}