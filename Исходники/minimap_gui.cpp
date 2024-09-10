void MinimapGui::presentMap(const CreatureView* creature, Rectangle bounds, Renderer& r,
    function<void(double, double)> clickFun) {
  const Level* level = creature->getLevel();
  double scale = min(double(bounds.getW()) / level->getBounds().getW(),
      double(bounds.getH()) / level->getBounds().getH());
  while (1) {
    update(level, level->getBounds(), creature, true);
    renderMap(r, Rectangle(Vec2(0, 0), embed(level->getBounds().getBottomRight(), bounds.getBottomRight())));
    r.drawAndClearBuffer();
    Event event;
    while (r.pollEvent(event)) {
      if (event.type == Event::KeyPressed)
        return;
      if (event.type == Event::MouseButtonPressed) {
        clickFun(double(event.mouseButton.x) / scale, double(event.mouseButton.y) / scale);
        return;
      }
    }
  }
}