void WebTestThemeEngineMock::paint(
    blink::WebCanvas* canvas,
    WebThemeEngine::Part part,
    WebThemeEngine::State state,
    const blink::WebRect& rect,
    const WebThemeEngine::ExtraParams* extraParams)
{
    SkIRect irect = webRectToSkIRect(rect);
    SkPaint paint;

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

    int halfHeight = irect.height() / 2;
    int halfWidth = irect.width() / 2;
    int quarterHeight = irect.height() / 4;
    int quarterWidth = irect.width() / 4;
    int left = irect.fLeft;
    int right = irect.fRight;
    int top = irect.fTop;
    int bottom = irect.fBottom;

    switch (part) {
    case WebThemeEngine::PartScrollbarDownArrow:
        box(canvas, irect, bgColors[state]);
        triangle(canvas,
            left  + quarterWidth, top    + quarterHeight,
            right - quarterWidth, top    + quarterHeight,
            left  + halfWidth,    bottom - quarterHeight,
            edgeColor);
        markState(canvas, irect, state);
        break;

    case WebThemeEngine::PartScrollbarLeftArrow:
        box(canvas, irect, bgColors[state]);
        triangle(canvas,
            right - quarterWidth, top    + quarterHeight,
            right - quarterWidth, bottom - quarterHeight,
            left  + quarterWidth, top    + halfHeight,
            edgeColor);
        break;

    case WebThemeEngine::PartScrollbarRightArrow:
        box(canvas, irect, bgColors[state]);
        triangle(canvas,
            left  + quarterWidth, top    + quarterHeight,
            right - quarterWidth, top    + halfHeight,
            left  + quarterWidth, bottom - quarterHeight,
            edgeColor);
        break;

    case WebThemeEngine::PartScrollbarUpArrow:
        box(canvas, irect, bgColors[state]);
        triangle(canvas,
            left  + quarterWidth, bottom - quarterHeight,
            left  + halfWidth,    top    + quarterHeight,
            right - quarterWidth, bottom - quarterHeight,
            edgeColor);
        markState(canvas, irect, state);
        break;

    case WebThemeEngine::PartScrollbarHorizontalThumb: {
        // Draw a narrower box on top of the outside box.
        nestedBoxes(canvas, irect, thumbLongIndent, thumbShortIndent,
            thumbLongIndent, thumbShortIndent,
            bgColors[state], bgColors[state]);
        // Draw a horizontal crosshatch for the grip.
        int longOffset = halfWidth - gripLongIndent;
        line(canvas,
            left  + gripLongIndent, top    + halfHeight,
            right - gripLongIndent, top    + halfHeight,
            edgeColor);
        line(canvas,
            left  + longOffset,     top    + gripShortIndent,
            left  + longOffset,     bottom - gripShortIndent,
            edgeColor);
        line(canvas,
            right - longOffset,     top    + gripShortIndent,
            right - longOffset,     bottom - gripShortIndent,
            edgeColor);
        markState(canvas, irect, state);
        break;
    }

    case WebThemeEngine::PartScrollbarVerticalThumb: {
        // Draw a shorter box on top of the outside box.
        nestedBoxes(canvas, irect, thumbShortIndent, thumbLongIndent,
            thumbShortIndent, thumbLongIndent,
            bgColors[state], bgColors[state]);
        // Draw a vertical crosshatch for the grip.
        int longOffset = halfHeight - gripLongIndent;
        line(canvas,
            left  + halfWidth,       top    + gripLongIndent,
            left  + halfWidth,       bottom - gripLongIndent,
            edgeColor);
        line(canvas,
            left  + gripShortIndent, top    + longOffset,
            right - gripShortIndent, top    + longOffset,
            edgeColor);
        line(canvas,
            left  + gripShortIndent, bottom - longOffset,
            right - gripShortIndent, bottom - longOffset,
            edgeColor);
        markState(canvas, irect, state);
        break;
    }

    case WebThemeEngine::PartScrollbarHorizontalTrack: {
        int longOffset = halfHeight - notchLongOffset;
        int shortOffset = irect.width() - notchShortOffset;
        if (extraParams->scrollbarTrack.isBack) {
            // back, notch on left
            nestedBoxes(canvas, irect, noOffset, longOffset, shortOffset,
                longOffset, bgColors[state], edgeColor);
        } else {
            // forward, notch on right
            nestedBoxes(canvas, irect, shortOffset, longOffset, noOffset,
                longOffset, bgColors[state], edgeColor);
        }

        markState(canvas, irect, state);
        break;
    }

    case WebThemeEngine::PartScrollbarVerticalTrack: {
        int longOffset = halfWidth - notchLongOffset;
        int shortOffset = irect.height() - notchShortOffset;
        if (extraParams->scrollbarTrack.isBack) {
            // back, notch at top
            nestedBoxes(canvas, irect, longOffset, noOffset, longOffset,
                shortOffset, bgColors[state], edgeColor);
        } else {
            // forward, notch at bottom
            nestedBoxes(canvas, irect, longOffset, shortOffset, longOffset,
                noOffset, bgColors[state], edgeColor);
        }

        markState(canvas, irect, state);
        break;
    }

    case WebThemeEngine::PartCheckbox:
        if (extraParams->button.indeterminate) {
            nestedBoxes(canvas, irect,
                checkIndent, halfHeight,
                checkIndent, halfHeight,
                bgColors[state], edgeColor);
        } else if (extraParams->button.checked) {
            irect = validate(irect, part);
            nestedBoxes(canvas, irect,
                checkIndent, checkIndent,
                checkIndent, checkIndent,
                bgColors[state], edgeColor);
        } else {
            irect = validate(irect, part);
            box(canvas, irect, bgColors[state]);
        }
        break;

    case WebThemeEngine::PartRadio:
        irect = validate(irect, part);
        halfHeight = irect.height() / 2;
        if (extraParams->button.checked) {
            circle(canvas, irect, SkIntToScalar(halfHeight), bgColors[state]);
            circle(canvas, irect, SkIntToScalar(halfHeight - checkIndent), edgeColor);
        } else {
            circle(canvas, irect, SkIntToScalar(halfHeight), bgColors[state]);
        }
        break;

    case WebThemeEngine::PartButton:
        roundRect(canvas, irect, bgColors[state]);
        markState(canvas, irect, state);
        break;

    case WebThemeEngine::PartTextField:
        paint.setColor(extraParams->textField.backgroundColor);
        paint.setStyle(SkPaint::kFill_Style);
        canvas->drawIRect(irect, paint);

        paint.setColor(edgeColor);
        paint.setStyle(SkPaint::kStroke_Style);
        canvas->drawIRect(irect, paint);

        markState(canvas, irect, state);
        break;

    case WebThemeEngine::PartMenuList:
        if (extraParams->menuList.fillContentArea) {
            box(canvas, irect, extraParams->menuList.backgroundColor);
        } else {
            SkPaint paint;
            paint.setColor(edgeColor);
            paint.setStyle(SkPaint::kStroke_Style);
            canvas->drawIRect(irect, paint);
        }

        // clip the drop-down arrow to be inside the select box
        if (extraParams->menuList.arrowX - 4 > irect.fLeft)
            irect.fLeft = extraParams->menuList.arrowX - 4;
        if (extraParams->menuList.arrowX + 12 < irect.fRight)
            irect.fRight = extraParams->menuList.arrowX + 12;

        irect.fTop = extraParams->menuList.arrowY - (extraParams->menuList.arrowHeight) / 2;
        irect.fBottom = extraParams->menuList.arrowY + (extraParams->menuList.arrowHeight - 1) / 2;
        halfWidth = irect.width() / 2;
        quarterWidth = irect.width() / 4;

        if (state == WebThemeEngine::StateFocused) // FIXME: draw differenty?
            state = WebThemeEngine::StateNormal;
        box(canvas, irect, bgColors[state]);
        triangle(canvas,
            irect.fLeft  + quarterWidth, irect.fTop,
            irect.fRight - quarterWidth, irect.fTop,
            irect.fLeft  + halfWidth,    irect.fBottom,
            edgeColor);

        break;

    case WebThemeEngine::PartSliderTrack: {
        SkIRect lirect =  irect;

        // Draw a narrow rect for the track plus box hatches on the ends.
        if (state == WebThemeEngine::StateFocused) // FIXME: draw differently?
            state = WebThemeEngine::StateNormal;
        if (extraParams->slider.vertical) {
            lirect.inset(halfWidth - sliderIndent, noOffset);
            box(canvas, lirect, bgColors[state]);
            line(canvas, left, top, right, top, edgeColor);
            line(canvas, left, bottom, right, bottom, edgeColor);
        } else {
            lirect.inset(noOffset, halfHeight - sliderIndent);
            box(canvas, lirect, bgColors[state]);
            line(canvas, left, top, left, bottom, edgeColor);
            line(canvas, right, top, right, bottom, edgeColor);
        }
        break;
    }

    case WebThemeEngine::PartSliderThumb:
        if (state == WebThemeEngine::StateFocused) // FIXME: draw differently?
            state = WebThemeEngine::StateNormal;
        oval(canvas, irect, bgColors[state]);
        break;

    case WebThemeEngine::PartInnerSpinButton: {
        // stack half-height up and down arrows on top of each other
        SkIRect lirect;
        int halfHeight = rect.height / 2;
        if (extraParams->innerSpin.readOnly)
            state = blink::WebThemeEngine::StateDisabled;

        lirect.set(rect.x, rect.y, rect.x + rect.width - 1, rect.y + halfHeight - 1);
        box(canvas, lirect, bgColors[state]);
        bottom = lirect.fBottom;
        quarterHeight = lirect.height() / 4;
        triangle(canvas,
            left  + quarterWidth, bottom - quarterHeight,
            right - quarterWidth, bottom - quarterHeight,
            left  + halfWidth,    top    + quarterHeight,
            edgeColor);

        lirect.set(rect.x, rect.y + halfHeight, rect.x + rect.width - 1,
            rect.y + 2 * halfHeight - 1);
        top = lirect.fTop;
        bottom = lirect.fBottom;
        quarterHeight = lirect.height() / 4;
        box(canvas, lirect, bgColors[state]);
        triangle(canvas,
            left  + quarterWidth, top    + quarterHeight,
            right - quarterWidth, top    + quarterHeight,
            left  + halfWidth,    bottom - quarterHeight,
            edgeColor);
        markState(canvas, irect, state);
        break;
    }
    case WebThemeEngine::PartProgressBar: {
        paint.setColor(bgColors[state]);
        paint.setStyle(SkPaint::kFill_Style);
        canvas->drawIRect(irect, paint);

        // Emulate clipping
        SkIRect tofill = irect;
        if (extraParams->progressBar.determinate) {
            tofill.set(extraParams->progressBar.valueRectX,
                extraParams->progressBar.valueRectY,
                extraParams->progressBar.valueRectX +
                extraParams->progressBar.valueRectWidth - 1,
                extraParams->progressBar.valueRectY +
                extraParams->progressBar.valueRectHeight);
        }

        tofill.intersect(irect, tofill);
        paint.setColor(edgeColor);
        paint.setStyle(SkPaint::kFill_Style);
        canvas->drawIRect(tofill, paint);

        markState(canvas, irect, state);
        break;
    }
    default:
        // FIXME: Should we do something here to indicate that we got an invalid part?
        // Unfortunately, we can't assert because we don't have access to WTF or base.
        break;
    }
}