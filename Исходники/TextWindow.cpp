bool TextWindow::handleMouseClick(RLMachine& machine, const Point& pos,
                                  bool pressed) {
  using namespace boost;

  if (inSelectionMode()) {
    bool found =
      find_if(selections_.begin(), selections_.end(),
              bind(&SelectionElement::handleMouseClick, _1, pos, pressed))
      != selections_.end();

    if (found)
      return true;
  }

  for (std::vector<std::pair<Point, int> >::const_iterator it =
           koe_replay_button_.begin(); it != koe_replay_button_.end(); ++it) {
    Rect r = Rect(textSurfaceRect().origin() + it->first,
                  koe_replay_info_->icon->size());
    if (r.contains(pos)) {
      // We only want to actually replay the voice clip once, but we want to
      // catch both clicks.
      if (pressed)
        system_.sound().koePlay(it->second);
      return true;
    }
  }

  if (isVisible() && !machine.system().graphics().interfaceHidden()) {
    return textbox_waku_->handleMouseClick(machine, pos, pressed);
  }

  return false;
}