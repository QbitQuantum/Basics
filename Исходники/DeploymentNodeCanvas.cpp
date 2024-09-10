int DeploymentNodeCanvas::min_width() {
  QFontMetrics fm(the_canvas()->get_font(UmlNormalFont));
  
  int wi;
  
  if (horiz)
    wi = fm.width(iname + ":" + browser_node->get_name());
  else {
    wi = fm.width(browser_node->get_name());
    
    int iw = fm.width(iname + ":");
    
    if (iw > wi)
      wi = iw;
  }
  
  const char * st = browser_node->get_data()->get_short_stereotype();
  
  if (st[0]) {
    int stw = fm.width(QString("<<") + toUnicode(st) + ">>");
    
    if (wi < stw)
      wi = stw;
  }
  
  wi += (int) ((DEPLOYMENTNODE_CANVAS_ADDED + 8) * the_canvas()->zoom());
  
  int min_w = (int) (DEPLOYMENTNODE_CANVAS_MIN_SIZE * the_canvas()->zoom());
  
  return (wi < min_w)
    ? min_w
    : wi;
}