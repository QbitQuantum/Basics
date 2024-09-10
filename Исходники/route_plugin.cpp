 void RoutePlugin::SetDrawStyle(QString style)
 {
   if (style == "lines")
   {
     draw_style_ = LINES;
   }
   else if (style == "points")
   {
     draw_style_ = POINTS;
   }
   DrawIcon();
 }