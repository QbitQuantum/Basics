bool ColorShades::onProcessMessage(ui::Message* msg)
{
  switch (msg->type()) {

    case ui::kOpenMessage:
      if (m_click == DragAndDropEntries) {
        // TODO This connection should be in the ContextBar
        m_conn = ColorBar::instance()->ChangeSelection.connect(
          base::Bind<void>(&ColorShades::onChangeColorBarSelection, this));
      }
      break;

    case ui::kSetCursorMessage:
      if (hasCapture()) {
        ui::set_mouse_cursor(ui::kMoveCursor);
        return true;
      }
      else if (m_click == ClickEntries &&
               m_hotIndex >= 0 &&
               m_hotIndex < int(m_shade.size())) {
        ui::set_mouse_cursor(ui::kHandCursor);
        return true;
      }
      break;

    case ui::kMouseEnterMessage:
    case ui::kMouseLeaveMessage:
      if (!hasCapture())
        m_hotIndex = -1;

      invalidate();
      break;

    case ui::kMouseDownMessage:
      if (m_hotIndex >= 0 &&
          m_hotIndex < int(m_shade.size())) {
        switch (m_click) {
          case ClickEntries:
            Click();
            m_hotIndex = -1;
            invalidate();
            break;
          case DragAndDropEntries:
            m_dragIndex = m_hotIndex;
            m_dropBefore = false;
            captureMouse();
            break;
        }
      }
      break;

    case ui::kMouseUpMessage: {
      if (m_click == ClickWholeShade) {
        setSelected(true);
        Click();
        closeWindow();
      }

      if (m_dragIndex >= 0) {
        ASSERT(m_dragIndex < int(m_shade.size()));

        auto color = m_shade[m_dragIndex];
        m_shade.erase(m_shade.begin()+m_dragIndex);
        if (m_hotIndex >= 0)
          m_shade.insert(m_shade.begin()+m_hotIndex, color);

        m_dragIndex = -1;
        invalidate();

        // Relayout the context bar if we have removed an entry.
        if (m_hotIndex < 0)
          parent()->parent()->layout();
      }

      if (hasCapture())
        releaseMouse();
      break;
    }

    case ui::kMouseMoveMessage: {
      ui::MouseMessage* mouseMsg = static_cast<ui::MouseMessage*>(msg);
      gfx::Point mousePos = mouseMsg->position() - bounds().origin();
      gfx::Rect bounds = clientBounds();
      int hot = -1;

      bounds.shrink(3*ui::guiscale());

      if (bounds.contains(mousePos)) {
        int count = size();
        hot = (mousePos.x - bounds.x) / (m_boxSize*ui::guiscale());
        hot = MID(0, hot, count-1);
      }

      if (m_hotIndex != hot) {
        m_hotIndex = hot;
        invalidate();
      }

      bool dropBefore =
        (hot >= 0 && mousePos.x < (bounds.x+m_boxSize*ui::guiscale()*hot)+m_boxSize*ui::guiscale()/2);
      if (m_dropBefore != dropBefore) {
        m_dropBefore = dropBefore;
        invalidate();
      }
      break;
    }
  }
  return Widget::onProcessMessage(msg);
}