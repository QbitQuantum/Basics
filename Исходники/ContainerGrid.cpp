void ContainerGrid::refresh() {
  renderer.setDrawColor(Color::BLACK);
  for (size_t i = 0; i != _linked.size(); ++i) {
    const px_t x = i % _cols, y = i / _cols;
    const auto slotRect =
        ScreenRect{x * (Client::ICON_SIZE + _gap + 2),
                   y * (Client::ICON_SIZE + _gap + 2) + 1,
                   Client::ICON_SIZE + 2, Client::ICON_SIZE + 2};
    if (_solidBackground) {
      static const auto SLOT_BACKGROUND_OFFSET = ScreenRect{1, 1, -2, -2};
      renderer.fillRect(slotRect + SLOT_BACKGROUND_OFFSET);
    }
    if (dragSlot != i ||
        dragGrid != this) {  // Don't draw an item being moved by the mouse.
      const std::pair<const ClientItem *, size_t> &slot = _linked[i];
      if (slot.first != nullptr) {
        slot.first->icon().draw(slotRect.x + 1, slotRect.y + 1);
        if (slot.second > 1) {
          Texture label(font(), makeArgs(slot.second), FONT_COLOR),
              labelOutline(font(), toString(slot.second), Color::UI_OUTLINE);
          px_t x = slotRect.x + slotRect.w - label.width() - 1,
               y = slotRect.y + slotRect.h - label.height() + textOffset;
          labelOutline.draw(x - 1, y);
          labelOutline.draw(x + 1, y);
          labelOutline.draw(x, y - 1);
          labelOutline.draw(x, y + 1);
          label.draw(x, y);
        }
      }
    }

    // Highlight moused-over slot
    if (_mouseOverSlot == i) {
      _highlight.draw(slotRect.x + 1, slotRect.y + 1);

      // Indicate matching gear slot if an item is being dragged
    } else if (_serial == Client::GEAR && dragGrid != nullptr) {
      size_t itemSlot = dragGrid->_linked[dragSlot].first->gearSlot();
      (i == itemSlot ? _highlightGood : _highlightBad)
          .draw(slotRect.x + 1, slotRect.y + 1);
    }
  }

  // Item tooltip
  if (_mouseOverSlot != NO_SLOT) {
    const ClientItem *item = _linked[_mouseOverSlot].first;
    if (item == nullptr)
      clearTooltip();
    else
      setTooltip(item->tooltip());
  }
}