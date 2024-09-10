void CoordEditWindow::layout()
 {
  Point size=getSize();

  spin.setPlace(Pane(Null,size.x,size.y/2));

  pos.x=size.x/2;
  pos.y=Div(3,4)*size.y;
 }