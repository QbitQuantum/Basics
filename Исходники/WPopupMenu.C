WPopupMenu::~WPopupMenu()
{
  if (button_) {
    WPushButton *b = dynamic_cast<WPushButton *>(button_);
    if (b)
      b->setMenu(0);
  }
}