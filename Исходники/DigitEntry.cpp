void
DigitEntry::OnPaint(Canvas &canvas)
{
    assert(cursor < length);

    const bool focused = HasCursorKeys() && HasFocus();

    if (HaveClipping())
        canvas.Clear(look.background_color);

    canvas.Select(look.text_font);
    canvas.SetBackgroundOpaque();

    const unsigned text_height = look.text_font.GetHeight();
    const int y = (top + bottom - text_height) / 2;

    PixelRect rc;
    rc.top = top;
    rc.bottom = bottom;

    TCHAR buffer[4];

    for (unsigned i = 0; i < length; ++i) {
        const Column &c = columns[i];

        rc.left = c.left;
        rc.right = c.right;

        if (focused && i == cursor) {
            canvas.SetTextColor(look.list.focused.text_color);
            canvas.SetBackgroundColor(look.list.focused.background_color);
        } else if (c.IsEditable()) {
            canvas.SetTextColor(look.list.text_color);
            canvas.SetBackgroundColor(look.list.background_color);
        } else {
            canvas.SetTextColor(look.list.text_color);
            canvas.SetBackgroundColor(look.background_color);
        }

        const TCHAR *text = buffer;
        buffer[1] = _T('\0');

        switch (c.type) {
        case Column::Type::DIGIT:
        case Column::Type::DIGIT6:
            assert(c.value < 10);
            buffer[0] = _T('0') + c.value;
            break;

        case Column::Type::HOUR:
            assert(c.value < 24);
            _stprintf(buffer, _T("%02u"), c.value);
            break;

        case Column::Type::DIGIT36:
            assert(c.value < 36);
            _stprintf(buffer, _T("%02u"), c.value);
            break;

        case Column::Type::DIGIT19:
            assert(c.value < 19);
            _stprintf(buffer, _T("%02u"), c.value);
            break;

        case Column::Type::SIGN:
            buffer[0] = c.IsNegative() ? _T('-') : _T('+');
            break;

        case Column::Type::DECIMAL_POINT:
            buffer[0] = _T('.');
            break;

        case Column::Type::COLON:
            buffer[0] = _T(':');
            break;

        case Column::Type::NORTH_SOUTH:
            buffer[0] = c.IsNegative() ? _T('S') : _T('N');
            break;

        case Column::Type::EAST_WEST:
            buffer[0] = c.IsNegative() ? _T('W') : _T('E');
            break;

        case Column::Type::DEGREES:
            text = _T("°");
            break;

        case Column::Type::APOSTROPHE:
            text = _T("'");
            break;

        case Column::Type::QUOTE:
            text = _T("\"");
            break;

        case Column::Type::UNIT:
            // TODO: render unit symbol?
            text = Units::unit_descriptors[c.value].name;
            break;
        }

        if (c.IsEditable() && !valid)
            buffer[0] = _T('\0');

        const int x = (c.left + c.right - canvas.CalcTextWidth(text)) / 2;

        canvas.DrawOpaqueText(x, y, rc, text);
    }

    canvas.SetBackgroundTransparent();
    canvas.SetTextColor(look.text_color);

    unsigned control_height = Layout::GetMaximumControlHeight();

    PixelRect plus_rc(0, top - control_height, 0, top);
    PixelRect minus_rc(0, bottom, 0, bottom + control_height);

    for (unsigned i = 0; i < length; ++i) {
        const Column &c = columns[i];
        if (!c.IsEditable())
            continue;

        plus_rc.left = minus_rc.left = c.left;
        plus_rc.right = minus_rc.right = c.right;

        button_renderer.DrawButton(canvas, plus_rc, false, false);
        button_renderer.DrawButton(canvas, minus_rc, false, false);

        canvas.SelectNullPen();
        canvas.Select(look.button.standard.foreground_brush);

        SymbolRenderer::DrawArrow(canvas, plus_rc, SymbolRenderer::UP);
        SymbolRenderer::DrawArrow(canvas, minus_rc, SymbolRenderer::DOWN);
    }
}