  void refreshPageList()
  {
    Window* root = d_guiContext->getRootWindow();
    // Check if the windows exists
    Listbox* lbox = 0;
    TabControl* tc = 0;

    if (root->isChild("Frame/TabControl/Page1/PageList"))
    {
      lbox = static_cast<Listbox*>(root->getChild(
        "Frame/TabControl/Page1/PageList"));
    }

    if (root->isChild("Frame/TabControl"))
    {
      tc = static_cast<TabControl*>(root->getChild(
        "Frame/TabControl"));
    }

    if (lbox && tc)
    {
      lbox->resetList();

      for (size_t i = 0; i < tc->getTabCount(); i++)
      {
        lbox->addItem(new MyListItem(
          tc->getTabContentsAtIndex(i)->getName()));
      }
    }
  }