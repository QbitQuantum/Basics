void ArtifactCanvas::compute_size() {
  used_color = (itscolor == UmlDefaultColor)
    ? the_canvas()->browser_diagram()->get_color(UmlArtifact)
    : itscolor;
  
  const BasicData * data = browser_node->get_data();
  QFontMetrics fm(the_canvas()->get_font(UmlNormalBoldFont));
  int he;
  int wi;
  
  const QPixmap * px = 
    ProfiledStereotypes::diagramPixmap(data->get_stereotype(),
				       the_canvas()->zoom());
  
  if (px != 0) {
    wi = fm.width(browser_node->get_name());
    if (wi < px->width())
      wi = px->width();
    
    he = px->height() + fm.height();
  }
  else {
    // <<artifact>>/stereotype on 2*font_height with the icon on the right
    // the icon height = 2*font_height
    // the icon width = 3*height/4
    // name on font_height+4 points
    const int four = (int) (4 * the_canvas()->zoom());
    int stw = fm.width((data->get_stereotype()[0])
		       ? (QString("<<") + toUnicode(data->get_short_stereotype()) + ">>")
		       : QString("<<artifact>>"))
      + 3*fm.height();
    
    
    he = 3*fm.height() + four;
    wi = fm.width(browser_node->get_name());
    
    if (wi < stw)
      wi = stw;
    
    wi += four*2;
    
    int min_w = (int) (ARTIFACT_CANVAS_MIN_SIZE * the_canvas()->zoom());
    
    if (wi <min_w) 
      wi = min_w;
    
    if (used_color != UmlTransparent) {
      const int shadow = the_canvas()->shadow();
      
      wi += shadow;
      he += shadow;
    }
  }
  
  // force odd width and height for line alignment
  DiagramCanvas::resize(wi | 1, he | 1);
}