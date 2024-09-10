void
GeometryTest::draw()
{
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  Display::draw_line(line1, Color(0.0f, 1.0f, 0.0f));
  Display::draw_line(line2, Color(0.0f, 1.0f, 0.0f));

  Display::fill_rect(Rectf(cursor - Vector2f(2,2), Sizef(5,5)),  Color(1.0f, 0.0f, 1.0f));
  Display::fill_rect(Rectf(cursor2 - Vector2f(2,2), Sizef(5,5)), Color(1.0f, 1.0f, 0.0f));

  Display::fill_rect(Rectf(collision_point - Vector2f(3,3), Sizef(7,7)), Color(1.0f, 1.0f, 1.0f));

  // Try vector projection
  Vector2f a(line1.p2 - line1.p1);
  Vector2f b(line2.p2 - line2.p1);
  Vector2f c(a.project(b));
  
  Display::draw_line(line1.p1, line1.p1 + c, Color(1.0f, 1.0f, 1.0f, 0.5f));

  int segments = std::max(0, int(cursor.y / 10));

  Display::fill_arc(Vector2f(200, 200), 100.0f, cursor.x, cursor2.x, Color(1.0f, 1.0f, 1.0f, 0.5f), segments);
  Display::draw_arc(Vector2f(200, 200), 100.0f, cursor.x, cursor2.x, Color(1.0f, 1.0f, 1.0f), segments);
  Display::draw_circle(Vector2f(200, 200), 128.0f, Color(1.0f, 1.0f, 1.0f), segments);
}