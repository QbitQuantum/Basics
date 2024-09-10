bool ColorButton::onProcessMessage(Message* msg)
{
    switch (msg->type()) {

    case kCloseMessage:
        if (m_window && m_window->isVisible())
            m_window->closeWindow(NULL);
        break;

    case kMouseEnterMessage:
        StatusBar::instance()->showColor(0, "", m_color, 255);
        break;

    case kMouseLeaveMessage:
        StatusBar::instance()->clearText();
        break;

    case kMouseMoveMessage:
        if (hasCapture()) {
            gfx::Point mousePos = static_cast<MouseMessage*>(msg)->position();
            Widget* picked = getManager()->pick(mousePos);
            app::Color color = m_color;

            if (picked && picked != this) {
                // Pick a color from another color-button
                if (ColorButton* pickedColBut = dynamic_cast<ColorButton*>(picked)) {
                    color = pickedColBut->getColor();
                }
                // Pick a color from the color-bar
                else if (picked->type == palette_view_type()) {
                    color = ((PaletteView*)picked)->getColorByPosition(mousePos.x, mousePos.y);
                }
                // Pick a color from a editor
                else if (picked->type == editor_type()) {
                    Editor* editor = static_cast<Editor*>(picked);
                    Sprite* sprite = editor->getSprite();
                    int x, y, imgcolor;

                    if (sprite) {
                        x = mousePos.x;
                        y = mousePos.y;
                        editor->screenToEditor(x, y, &x, &y);
                        imgcolor = sprite->getPixel(x, y, editor->getFrame());
                        color = app::Color::fromImage(sprite->getPixelFormat(), imgcolor);
                    }
                }
            }

            // Did the color change?
            if (color != m_color) {
                setColor(color);
            }
        }
        break;

    case kSetCursorMessage:
        if (hasCapture()) {
            jmouse_set_cursor(kEyedropperCursor);
            return true;
        }
        break;

    }

    return ButtonBase::onProcessMessage(msg);
}