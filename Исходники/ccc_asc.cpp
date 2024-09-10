GraphicWindow& GraphicWindow::operator<<(Circle c)
{
   ellipse(c.get_center().get_x(), c.get_center().get_y(),
         c.get_radius(), c.get_radius());
   return *this;
}