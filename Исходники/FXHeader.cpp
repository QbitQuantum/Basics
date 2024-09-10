// Draw item
void FXHeaderItem::draw(const FXHeader* header,FXDC& dc,FXint x,FXint y,FXint w,FXint h){
  register FXint tx,ty,tw,th,ix,iy,iw,ih,s,ml,mr,mt,mb,beg,end,t,xx,yy,bb,aa,ax,ay;
  register FXFont *font=header->getFont();

  // Get border width and padding
  bb=header->getBorderWidth();
  ml=header->getPadLeft()+bb;
  mr=header->getPadRight()+bb;
  mt=header->getPadTop()+bb;
  mb=header->getPadBottom()+bb;

  // Shrink by margins
  x+=ml; w-=ml+mr;
  y+=mt; h-=mt+mb;

  // Initial clip rectangle
  dc.setClipRectangle(x,y,w,h);

  // Text width and height
  tw=th=iw=ih=beg=s=0;
  do{
    end=beg;
    while(end<label.length() && label[end]!='\n') end++;
    if((t=font->getTextWidth(&label[beg],end-beg))>tw) tw=t;
    th+=font->getFontHeight();
    beg=end+1;
    }
  while(end<label.length());

  // Icon size
  if(icon){
    iw=icon->getWidth();
    ih=icon->getHeight();
    }

  // Icon-text spacing
  if(iw && tw) s=ICON_SPACING;

  // Draw arrows
  if(state&(ARROW_UP|ARROW_DOWN)){
    aa=(font->getFontHeight()-5)|1;
    ay=y+(h-aa)/2;
    ax=x+w-aa-2;
    if(state&ARROW_UP){
      dc.setForeground(header->getHiliteColor());
      dc.drawLine(ax+aa/2,ay,ax+aa-1,ay+aa);
      dc.drawLine(ax,ay+aa,ax+aa,ay+aa);
      dc.setForeground(header->getShadowColor());
      dc.drawLine(ax+aa/2,ay,ax,ay+aa);
      }
    else{
      dc.setForeground(header->getHiliteColor());
      dc.drawLine(ax+aa/2,ay+aa,ax+aa-1,ay);
      dc.setForeground(header->getShadowColor());
      dc.drawLine(ax+aa/2,ay+aa,ax,ay);
      dc.drawLine(ax,ay,ax+aa,ay);
      }
    w-=aa+4;
    dc.setClipRectangle(x,y,w,h);
    }

  // Fix x coordinate
  if(state&LEFT){
    if(state&BEFORE){ ix=x; tx=ix+iw+s; }
    else if(state&AFTER){ tx=x; ix=tx+tw+s; }
    else{ ix=x; tx=x; }
    }
  else if(state&RIGHT){
    if(state&BEFORE){ tx=x+w-tw; ix=tx-iw-s; }
    else if(state&AFTER){ ix=x+w-iw; tx=ix-tw-s; }
    else{ ix=x+w-iw; tx=x+w-tw; }
    }
  else{
    if(state&BEFORE){ ix=x+(w-tw-iw-s)/2; tx=ix+iw+s; }
    else if(state&AFTER){ tx=x+(w-tw-iw-s)/2; ix=tx+tw+s; }
    else{ ix=x+(w-iw)/2; tx=x+(w-tw)/2; }
    }

  // Fix y coordinate
  if(state&TOP){
    if(state&ABOVE){ iy=y; ty=iy+ih; }
    else if(state&BELOW){ ty=y; iy=ty+th; }
    else{ iy=y; ty=y; }
    }
  else if(state&BOTTOM){
    if(state&ABOVE){ ty=y+h-th; iy=ty-ih; }
    else if(state&BELOW){ iy=y+h-ih; ty=iy-th; }
    else{ iy=y+h-ih; ty=y+h-th; }
    }
  else{
    if(state&ABOVE){ iy=y+(h-th-ih)/2; ty=iy+ih; }
    else if(state&BELOW){ ty=y+(h-th-ih)/2; iy=ty+th; }
    else{ iy=y+(h-ih)/2; ty=y+(h-th)/2; }
    }

  // Offset a bit when pressed
  if(state&PRESSED){ tx++; ty++; ix++; iy++; }

  // Paint icon
  if(icon){
    dc.drawIcon(icon,ix,iy);
    }

  // Text color
  dc.setForeground(header->getTextColor());

  // Draw text
  yy=ty+font->getFontAscent();
  beg=0;
  do{
    end=beg;
    while(end<label.length() && label[end]!='\n') end++;
    if(state&LEFT) xx=tx;
    else if(state&RIGHT) xx=tx+tw-font->getTextWidth(&label[beg],end-beg);
    else xx=tx+(tw-font->getTextWidth(&label[beg],end-beg))/2;
    dc.drawText(xx,yy,&label[beg],end-beg);
    yy+=font->getFontHeight();
    beg=end+1;
    }
  while(end<label.length());

  // Restore original clip path
  dc.clearClipRectangle();
  }