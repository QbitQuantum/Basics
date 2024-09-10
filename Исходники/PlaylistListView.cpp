void
PlaylistListView::Item::Draw(BView* owner, BRect frame, const font_height& fh,
                             bool tintedLine, uint32 mode, bool active, uint32 playbackState)
{
    rgb_color color = (rgb_color) {
        255, 255, 255, 255
    };
    if (tintedLine)
        color = tint_color(color, 1.04);
    // background
    if (IsSelected())
        color = tint_color(color, B_DARKEN_2_TINT);
    owner->SetLowColor(color);
    owner->FillRect(frame, B_SOLID_LOW);
    // label
    rgb_color black = (rgb_color) {
        0, 0, 0, 255
    };
    owner->SetHighColor(black);
    const char* text = Text();
    switch (mode) {
    case DISPLAY_NAME:
        // TODO
        break;
    case DISPLAY_PATH:
        // TODO
        break;
    default:
        break;
    }

    float playbackMarkSize = playback_mark_size(fh);
    float textOffset = text_offset(fh);

    BString truncatedString(text);
    owner->TruncateString(&truncatedString, B_TRUNCATE_MIDDLE,
                          frame.Width() - playbackMarkSize - textOffset);
    owner->DrawString(truncatedString.String(),
                      BPoint(frame.left + playbackMarkSize + textOffset,
                             floorf(frame.top + frame.bottom + fh.ascent) / 2 - 1));

    // playmark
    if (active) {
        rgb_color green = (rgb_color) {
            0, 255, 0, 255
        };
        if (playbackState != PLAYBACK_STATE_PLAYING)
            green = tint_color(color, B_DARKEN_1_TINT);

        BRect r(0, 0, playbackMarkSize, playbackMarkSize);
        r.OffsetTo(frame.left + 4,
                   ceilf((frame.top + frame.bottom - playbackMarkSize) / 2));

#ifdef __ANTARES__
        uint32 flags = owner->Flags();
        owner->SetFlags(flags | B_SUBPIXEL_PRECISE);

        BShape shape;
        shape.MoveTo(r.LeftTop());
        shape.LineTo(r.LeftBottom());
        shape.LineTo(BPoint(r.right, (r.top + r.bottom) / 2));
        shape.Close();

        owner->MovePenTo(B_ORIGIN);
        owner->FillShape(&shape);

        shape.Clear();
        r.InsetBy(1, 1);
        shape.MoveTo(r.LeftTop());
        shape.LineTo(r.LeftBottom());
        shape.LineTo(BPoint(r.right, (r.top + r.bottom) / 2));
        shape.Close();

        BGradientLinear gradient;
        gradient.SetStart(r.LeftTop());
        gradient.SetEnd(r.LeftBottom());
        gradient.AddColor(tint_color(green, B_LIGHTEN_1_TINT), 0);
        gradient.AddColor(tint_color(green, B_DARKEN_1_TINT), 255.0);

        owner->FillShape(&shape, gradient);

        owner->SetFlags(flags);
#else
        BPoint arrow[3];
        arrow[0] = r.LeftTop();
        arrow[1] = r.LeftBottom();
        arrow[2].x = r.right;
        arrow[2].y = (r.top + r.bottom) / 2;

        rgb_color lightGreen = tint_color(green, B_LIGHTEN_2_TINT);
        rgb_color darkGreen = tint_color(green, B_DARKEN_2_TINT);
        owner->BeginLineArray(6);
        // black outline
        owner->AddLine(arrow[0], arrow[1], black);
        owner->AddLine(BPoint(arrow[1].x + 1.0, arrow[1].y - 1.0),
                       arrow[2], black);
        owner->AddLine(arrow[0], arrow[2], black);
        // inset arrow
        arrow[0].x += 1.0;
        arrow[0].y += 2.0;
        arrow[1].x += 1.0;
        arrow[1].y -= 2.0;
        arrow[2].x -= 2.0;
        // highlights and shadow
        owner->AddLine(arrow[1], arrow[2], darkGreen);
        owner->AddLine(arrow[0], arrow[2], lightGreen);
        owner->AddLine(arrow[0], arrow[1], lightGreen);
        owner->EndLineArray();
        // fill green
        arrow[0].x += 1.0;
        arrow[0].y += 1.0;
        arrow[1].x += 1.0;
        arrow[1].y -= 1.0;
        arrow[2].x -= 2.0;

        owner->SetLowColor(owner->HighColor());
        owner->SetHighColor(green);
        owner->FillPolygon(arrow, 3);
#endif // __ANTARES__
    }
}