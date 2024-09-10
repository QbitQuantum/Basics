// Draw item
void GMListItem::draw(const GMList* list,FXDC& dc,FXint xx,FXint yy,FXint ww,FXint hh) const {
  FXFont *font=list->getFont();
  FXint ih=0,th=0;
  if(icon) ih=icon->getHeight();
  if(!label.empty()) th=font->getFontHeight();
  if(isSelected())
    dc.setForeground(list->getSelBackColor());
//  else
//    dc.setForeground(list->getBackColor());     // FIXME maybe paint background in onPaint?

  dc.fillRectangle(xx,yy,ww,hh);
  if(hasFocus()){
    dc.drawFocusRectangle(xx+1,yy+1,ww-2,hh-2);
    }
  xx+=SIDE_SPACING/2;
  if(icon){
    dc.drawIcon(icon,xx,yy+(hh-ih)/2);
    xx+=ICON_SPACING+icon->getWidth();
    }
  if(!label.empty()){
    if(!isEnabled())
      dc.setForeground(makeShadowColor(list->getBackColor()));
    else if(isSelected())
      dc.setForeground(list->getSelTextColor());
    else
      dc.setForeground(list->getTextColor());
    dc.drawText(xx,yy+(hh-th)/2+font->getFontAscent(),label);
    }
  }