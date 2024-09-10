void Layer::onButtonClicked(input::Button button, bool clicked)
{
  vec2 cursorPosition = vec2(window.getCursorPosition());
  cursorPosition.y = window.getHeight() - cursorPosition.y;

  if (clicked)
  {
    Widget* clickedWidget = NULL;

    if (captureWidget)
      clickedWidget = captureWidget;
    else
    {
      for (auto w = roots.rbegin();  w != roots.rend();  w++)
      {
        if ((*w)->isVisible())
        {
          clickedWidget = (*w)->findByPoint(cursorPosition);
          if (clickedWidget)
            break;
        }
      }
    }

    while (clickedWidget && !clickedWidget->isEnabled())
      clickedWidget = clickedWidget->getParent();

    if (clickedWidget)
    {
      clickedWidget->activate();
      clickedWidget->buttonClickedSignal(*clickedWidget,
                                         cursorPosition,
                                         button,
                                         clicked);

      if (!captureWidget && clickedWidget->isDraggable())
        draggedWidget = clickedWidget;
    }
  }
  else
  {
    if (draggedWidget)
    {
      if (dragging)
      {
        draggedWidget->dragEndedSignal(*draggedWidget, cursorPosition);
        dragging = false;
      }

      draggedWidget = NULL;
    }

    if (activeWidget)
    {
      if (captureWidget || activeWidget->getGlobalArea().contains(cursorPosition))
      {
        activeWidget->buttonClickedSignal(*activeWidget,
                                          cursorPosition,
                                          button,
                                          clicked);
      }
    }
  }
}