void StyleAdjuster::adjustStyleForHTMLElement(ComputedStyle& style, const ComputedStyle& parentStyle, HTMLElement& element)
{
    // <div> and <span> are the most common elements on the web, we skip all the work for them.
    if (isHTMLDivElement(element) || isHTMLSpanElement(element))
        return;

    if (isHTMLTableCellElement(element)) {
        // If we have a <td> that specifies a float property, in quirks mode we just drop the float property.
        // FIXME: Why is this only <td> and not <th>?
        if (element.hasTagName(tdTag) && m_useQuirksModeStyles) {
            style.setDisplay(TABLE_CELL);
            style.setFloating(NoFloat);
        }
        // FIXME: We shouldn't be overriding start/-webkit-auto like this. Do it in html.css instead.
        // Table headers with a text-align of -webkit-auto will change the text-align to center.
        if (element.hasTagName(thTag) && style.textAlign() == TASTART)
            style.setTextAlign(CENTER);
        if (style.whiteSpace() == KHTML_NOWRAP) {
            // Figure out if we are really nowrapping or if we should just
            // use normal instead. If the width of the cell is fixed, then
            // we don't actually use NOWRAP.
            if (style.width().isFixed())
                style.setWhiteSpace(NORMAL);
            else
                style.setWhiteSpace(NOWRAP);
        }
        return;
    }

    if (isHTMLTableElement(element)) {
        // Sites commonly use display:inline/block on <td>s and <table>s. In quirks mode we force
        // these tags to retain their display types.
        if (m_useQuirksModeStyles)
            style.setDisplay(style.isDisplayInlineType() ? INLINE_TABLE : TABLE);
        // Tables never support the -webkit-* values for text-align and will reset back to the default.
        if (style.textAlign() == WEBKIT_LEFT || style.textAlign() == WEBKIT_CENTER || style.textAlign() == WEBKIT_RIGHT)
            style.setTextAlign(TASTART);
        return;
    }

    if (isHTMLFrameElement(element) || isHTMLFrameSetElement(element)) {
        // Frames and framesets never honor position:relative or position:absolute. This is necessary to
        // fix a crash where a site tries to position these objects. They also never honor display.
        style.setPosition(StaticPosition);
        style.setDisplay(BLOCK);
        return;
    }

    if (isHTMLRTElement(element)) {
        // Ruby text does not support float or position. This might change with evolution of the specification.
        style.setPosition(StaticPosition);
        style.setFloating(NoFloat);
        return;
    }

    if (isHTMLLegendElement(element)) {
        style.setDisplay(BLOCK);
        return;
    }

    if (isHTMLMarqueeElement(element)) {
        // For now, <marquee> requires an overflow clip to work properly.
        style.setOverflowX(OHIDDEN);
        style.setOverflowY(OHIDDEN);
        return;
    }

    if (isHTMLTextAreaElement(element)) {
        // Textarea considers overflow visible as auto.
        style.setOverflowX(style.overflowX() == OVISIBLE ? OAUTO : style.overflowX());
        style.setOverflowY(style.overflowY() == OVISIBLE ? OAUTO : style.overflowY());
        return;
    }

    if (isHTMLPlugInElement(element)) {
        style.setRequiresAcceleratedCompositingForExternalReasons(toHTMLPlugInElement(element).shouldAccelerate());

        // Plugins should get the standard replaced width/height instead of 'auto'.
        // Replaced layoutObjects get this for free, and fallback content doesn't count.
        if (toHTMLPlugInElement(element).usePlaceholderContent()) {
            if (style.width().isAuto())
                style.setWidth(Length(LayoutReplaced::defaultWidth, Fixed));
            if (style.height().isAuto())
                style.setHeight(Length(LayoutReplaced::defaultHeight, Fixed));
        }

        return;
    }
}