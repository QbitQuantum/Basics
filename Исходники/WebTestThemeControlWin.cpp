void WebTestThemeControlWin::draw()
{
    int halfWidth = m_width / 2;
    int halfHeight = m_height / 2;
    int quarterWidth = m_width / 4;
    int quarterHeight = m_height / 4;

    // Indent amounts for the check in a checkbox or radio button.
    const int checkIndent = 3;

    // Indent amounts for short and long sides of the scrollbar notches.
    const int notchLongOffset = 1;
    const int notchShortOffset = 4;
    const int noOffset = 0;

    // Indent amounts for the short and long sides of a scroll thumb box.
    const int thumbLongIndent = 0;
    const int thumbShortIndent = 2;

    // Indents for the crosshatch on a scroll grip.
    const int gripLongIndent = 3;
    const int gripShortIndent = 5;

    // Indents for the the slider track.
    const int sliderIndent = 2;

    switch (m_type) {
    case UnknownType:
        BLINK_ASSERT_NOT_REACHED();
        break;

    case TextFieldType:
        // We render this by hand outside of this function.
        BLINK_ASSERT_NOT_REACHED();
        break;

    case PushButtonType:
        // push buttons render as a rounded rectangle
        roundRect(m_bgColor);
        break;

    case UncheckedBoxType:
        // Unchecked boxes are simply plain boxes.
        box(m_irect, m_bgColor);
        break;

    case CheckedBoxType:
        nestedBoxes(checkIndent, checkIndent, checkIndent, checkIndent, m_bgColor, m_fgColor);
        break;

    case IndeterminateCheckboxType:
        // Indeterminate checkbox is a box containing '-'.
        nestedBoxes(checkIndent, halfHeight, checkIndent, halfHeight, m_bgColor, m_fgColor);
        break;

    case UncheckedRadioType:
        circle(SkIntToScalar(halfHeight), m_bgColor);
        break;

    case CheckedRadioType:
        circle(SkIntToScalar(halfHeight), m_bgColor);
        circle(SkIntToScalar(halfHeight - checkIndent), m_fgColor);
        break;

    case HorizontalScrollTrackBackType: {
        // Draw a box with a notch at the left.
        int longOffset = halfHeight - notchLongOffset;
        int shortOffset = m_width - notchShortOffset;
        nestedBoxes(noOffset, longOffset, shortOffset, longOffset, m_bgColor, m_edgeColor);
        break;
    }

    case HorizontalScrollTrackForwardType: {
        // Draw a box with a notch at the right.
        int longOffset  = halfHeight - notchLongOffset;
        int shortOffset = m_width - notchShortOffset;
        nestedBoxes(shortOffset, longOffset, noOffset, longOffset, m_bgColor, m_fgColor);
        break;
    }

    case VerticalScrollTrackBackType: {
        // Draw a box with a notch at the top.
        int longOffset  = halfWidth - notchLongOffset;
        int shortOffset = m_height - notchShortOffset;
        nestedBoxes(longOffset, noOffset, longOffset, shortOffset, m_bgColor, m_fgColor);
        break;
    }

    case VerticalScrollTrackForwardType: {
        // Draw a box with a notch at the bottom.
        int longOffset  = halfWidth - notchLongOffset;
        int shortOffset = m_height - notchShortOffset;
        nestedBoxes(longOffset, shortOffset, longOffset, noOffset, m_bgColor, m_fgColor);
        break;
    }

    case HorizontalScrollThumbType:
        // Draw a narrower box on top of the outside box.
        nestedBoxes(thumbLongIndent, thumbShortIndent, thumbLongIndent, thumbShortIndent, m_bgColor, m_bgColor);
        break;

    case VerticalScrollThumbType:
        // Draw a shorter box on top of the outside box.
        nestedBoxes(thumbShortIndent, thumbLongIndent, thumbShortIndent, thumbLongIndent, m_bgColor, m_bgColor);
        break;

    case HorizontalSliderThumbType:
    case VerticalSliderThumbType:
        // Slider thumbs are ovals.
        oval(m_bgColor);
        break;

    case HorizontalScrollGripType: {
        // Draw a horizontal crosshatch for the grip.
        int longOffset = halfWidth - gripLongIndent;
        line(m_left + gripLongIndent, m_top + halfHeight, m_right - gripLongIndent, m_top + halfHeight, m_fgColor);
        line(m_left + longOffset, m_top + gripShortIndent, m_left + longOffset, m_bottom - gripShortIndent, m_fgColor);
        line(m_right - longOffset, m_top + gripShortIndent, m_right - longOffset, m_bottom - gripShortIndent, m_fgColor);
        break;
    }

    case VerticalScrollGripType: {
        // Draw a vertical crosshatch for the grip.
        int longOffset = halfHeight - gripLongIndent;
        line(m_left + halfWidth, m_top + gripLongIndent, m_left + halfWidth, m_bottom - gripLongIndent, m_fgColor);
        line(m_left + gripShortIndent, m_top + longOffset, m_right - gripShortIndent, m_top + longOffset, m_fgColor);
        line(m_left + gripShortIndent, m_bottom - longOffset, m_right - gripShortIndent, m_bottom - longOffset, m_fgColor);
        break;
    }

    case LeftArrowType:
        // Draw a left arrow inside a box.
        box(m_irect, m_bgColor);
        triangle(m_right - quarterWidth, m_top + quarterHeight, m_right - quarterWidth, m_bottom - quarterHeight, m_left + quarterWidth, m_top + halfHeight, m_fgColor);
        break;

    case RightArrowType:
        // Draw a left arrow inside a box.
        box(m_irect, m_bgColor);
        triangle(m_left + quarterWidth, m_top + quarterHeight, m_right - quarterWidth, m_top + halfHeight, m_left + quarterWidth, m_bottom - quarterHeight, m_fgColor);
        break;

    case UpArrowType:
        // Draw an up arrow inside a box.
        box(m_irect, m_bgColor);
        triangle(m_left + quarterWidth, m_bottom - quarterHeight, m_left + halfWidth, m_top + quarterHeight, m_right - quarterWidth, m_bottom - quarterHeight, m_fgColor);
        break;

    case DownArrowType:
        // Draw a down arrow inside a box.
        box(m_irect, m_bgColor);
        triangle(m_left + quarterWidth, m_top + quarterHeight, m_right - quarterWidth, m_top + quarterHeight, m_left + halfWidth, m_bottom - quarterHeight, m_fgColor);
        break;

    case HorizontalSliderTrackType: {
        // Draw a narrow rect for the track plus box hatches on the ends.
        SkIRect lirect;
        lirect = m_irect;
        lirect.inset(noOffset, halfHeight - sliderIndent);
        box(lirect, m_bgColor);
        line(m_left,  m_top, m_left,  m_bottom, m_edgeColor);
        line(m_right, m_top, m_right, m_bottom, m_edgeColor);
        break;
    }

    case VerticalSliderTrackType: {
        // Draw a narrow rect for the track plus box hatches on the ends.
        SkIRect lirect;
        lirect = m_irect;
        lirect.inset(halfWidth - sliderIndent, noOffset);
        box(lirect, m_bgColor);
        line(m_left, m_top, m_right, m_top, m_edgeColor);
        line(m_left, m_bottom, m_right, m_bottom, m_edgeColor);
        break;
    }

    case DropDownButtonType:
        // Draw a box with a big down arrow on top.
        box(m_irect, m_bgColor);
        triangle(m_left + quarterWidth, m_top, m_right - quarterWidth, m_top, m_left + halfWidth, m_bottom, m_fgColor);
        break;

    default:
        BLINK_ASSERT_NOT_REACHED();
        break;
    }

    markState();
}