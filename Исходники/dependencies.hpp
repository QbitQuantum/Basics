inline bool operator==(const Gdk::Rectangle& a, const Gdk::Rectangle& b)
{
  return a.get_x()==b.get_x() && a.get_y()==b.get_y() && a.get_width()==b.get_width() && a.get_height()==b.get_height();
}