//----------------------------------------------------------------------------//
float FalagardEditbox::calculateTextOffset(const Rectf& text_area,
                                           const float text_extent,
                                           const float caret_width,
                                           const float extent_to_caret)
{
    // if caret is to the left of the box
    if ((d_lastTextOffset + extent_to_caret) < 0)
        return -extent_to_caret;

    // if caret is off to the right.
    if ((d_lastTextOffset + extent_to_caret) >= (text_area.getWidth() - caret_width))
        return text_area.getWidth() - extent_to_caret - caret_width;

    // handle formatting of text when it's shorter than the available space
    if (text_extent < text_area.getWidth())
    {
        if (d_textFormatting == HTF_CENTRE_ALIGNED)
            return (text_area.getWidth() - text_extent) / 2;

        if (d_textFormatting == HTF_RIGHT_ALIGNED)
            return text_area.getWidth() - text_extent;
    }

    // no change to text position; re-use last offset value.
    return d_lastTextOffset;
}