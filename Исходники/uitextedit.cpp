void UITextEdit::update(bool focusCursor)
{
    if(!m_updatesEnabled)
        return;

    std::string text = getDisplayedText();
    m_drawText = text;
    int textLength = text.length();

    // prevent glitches
    if(m_rect.isEmpty())
        return;

    // map glyphs positions
    Size textBoxSize;
    const std::vector<Point>& glyphsPositions = m_font->calculateGlyphsPositions(text, m_textAlign, &textBoxSize);
    const Rect *glyphsTextureCoords = m_font->getGlyphsTextureCoords();
    const Size *glyphsSize = m_font->getGlyphsSize();
    int glyph;

    // update rect size
    if(!m_rect.isValid() || m_textHorizontalAutoResize || m_textVerticalAutoResize) {
        textBoxSize += Size(m_padding.left + m_padding.right, m_padding.top + m_padding.bottom) + m_textOffset.toSize();
        Size size = getSize();
        if(size.width() <= 0 || (m_textHorizontalAutoResize && !m_textWrap))
            size.setWidth(textBoxSize.width());
        if(size.height() <= 0 || m_textVerticalAutoResize)
            size.setHeight(textBoxSize.height());
        setSize(size);
    }

    // resize just on demand
    if(textLength > (int)m_glyphsCoords.size()) {
        m_glyphsCoords.resize(textLength);
        m_glyphsTexCoords.resize(textLength);
    }

    Point oldTextAreaOffset = m_textVirtualOffset;

    if(textBoxSize.width() <= getPaddingRect().width())
        m_textVirtualOffset.x = 0;
    if(textBoxSize.height() <= getPaddingRect().height())
        m_textVirtualOffset.y = 0;

    // readjust start view area based on cursor position
    m_cursorInRange = false;
    if(focusCursor && m_autoScroll) {
        if(m_cursorPos > 0 && textLength > 0) {
                assert(m_cursorPos <= textLength);
                Rect virtualRect(m_textVirtualOffset, m_rect.size() - Size(m_padding.left+m_padding.right, 0)); // previous rendered virtual rect
                int pos = m_cursorPos - 1; // element before cursor
                glyph = (uchar)text[pos]; // glyph of the element before cursor
                Rect glyphRect(glyphsPositions[pos], glyphsSize[glyph]);

                // if the cursor is not on the previous rendered virtual rect we need to update it
                if(!virtualRect.contains(glyphRect.topLeft()) || !virtualRect.contains(glyphRect.bottomRight())) {
                    // calculate where is the first glyph visible
                    Point startGlyphPos;
                    startGlyphPos.y = std::max(glyphRect.bottom() - virtualRect.height(), 0);
                    startGlyphPos.x = std::max(glyphRect.right() - virtualRect.width(), 0);

                    // find that glyph
                    for(pos = 0; pos < textLength; ++pos) {
                        glyph = (uchar)text[pos];
                        glyphRect = Rect(glyphsPositions[pos], glyphsSize[glyph]);
                        glyphRect.setTop(std::max(glyphRect.top() - m_font->getYOffset() - m_font->getGlyphSpacing().height(), 0));
                        glyphRect.setLeft(std::max(glyphRect.left() - m_font->getGlyphSpacing().width(), 0));

                        // first glyph entirely visible found
                        if(glyphRect.topLeft() >= startGlyphPos) {
                            m_textVirtualOffset.x = glyphsPositions[pos].x;
                            m_textVirtualOffset.y = glyphsPositions[pos].y - m_font->getYOffset();
                            break;
                        }
                    }
                }
        } else {
            m_textVirtualOffset = Point(0,0);
        }
        m_cursorInRange = true;
    } else {
        if(m_cursorPos > 0 && textLength > 0) {
            Rect virtualRect(m_textVirtualOffset, m_rect.size() - Size(2*m_padding.left+m_padding.right, 0) ); // previous rendered virtual rect
            int pos = m_cursorPos - 1; // element before cursor
            glyph = (uchar)text[pos]; // glyph of the element before cursor
            Rect glyphRect(glyphsPositions[pos], glyphsSize[glyph]);
            if(virtualRect.contains(glyphRect.topLeft()) && virtualRect.contains(glyphRect.bottomRight()))
                m_cursorInRange = true;
        } else {
            m_cursorInRange = true;
        }
    }

    bool fireAreaUpdate = false;
    if(oldTextAreaOffset != m_textVirtualOffset)
        fireAreaUpdate = true;

    Rect textScreenCoords = m_rect;
    textScreenCoords.expandLeft(-m_padding.left);
    textScreenCoords.expandRight(-m_padding.right);
    textScreenCoords.expandBottom(-m_padding.bottom);
    textScreenCoords.expandTop(-m_padding.top);
    m_drawArea = textScreenCoords;

    if(textScreenCoords.size() != m_textVirtualSize) {
        m_textVirtualSize = textScreenCoords.size();
        fireAreaUpdate = true;
    }

    Size totalSize = textBoxSize;
    if(totalSize.width() < m_textVirtualSize.width())
        totalSize.setWidth(m_textVirtualSize.height());
    if(totalSize.height() < m_textVirtualSize.height())
        totalSize.setHeight(m_textVirtualSize.height());
    if(m_textTotalSize != totalSize) {
        m_textTotalSize = totalSize;
        fireAreaUpdate = true;
    }

    if(m_textAlign & Fw::AlignBottom) {
        m_drawArea.translate(0, textScreenCoords.height() - textBoxSize.height());
    } else if(m_textAlign & Fw::AlignVerticalCenter) {
        m_drawArea.translate(0, (textScreenCoords.height() - textBoxSize.height()) / 2);
    } else { // AlignTop
    }

    if(m_textAlign & Fw::AlignRight) {
        m_drawArea.translate(textScreenCoords.width() - textBoxSize.width(), 0);
    } else if(m_textAlign & Fw::AlignHorizontalCenter) {
        m_drawArea.translate((textScreenCoords.width() - textBoxSize.width()) / 2, 0);
    } else { // AlignLeft

    }

    for(int i = 0; i < textLength; ++i) {
        glyph = (uchar)text[i];
        m_glyphsCoords[i].clear();

        // skip invalid glyphs
        if(glyph < 32 && glyph != (uchar)'\n')
            continue;

        // calculate initial glyph rect and texture coords
        Rect glyphScreenCoords(glyphsPositions[i], glyphsSize[glyph]);
        Rect glyphTextureCoords = glyphsTextureCoords[glyph];

        // first translate to align position
        if(m_textAlign & Fw::AlignBottom) {
            glyphScreenCoords.translate(0, textScreenCoords.height() - textBoxSize.height());
        } else if(m_textAlign & Fw::AlignVerticalCenter) {
            glyphScreenCoords.translate(0, (textScreenCoords.height() - textBoxSize.height()) / 2);
        } else { // AlignTop
            // nothing to do
        }

        if(m_textAlign & Fw::AlignRight) {
            glyphScreenCoords.translate(textScreenCoords.width() - textBoxSize.width(), 0);
        } else if(m_textAlign & Fw::AlignHorizontalCenter) {
            glyphScreenCoords.translate((textScreenCoords.width() - textBoxSize.width()) / 2, 0);
        } else { // AlignLeft
            // nothing to do
        }

        // only render glyphs that are after startRenderPosition
        if(glyphScreenCoords.bottom() < m_textVirtualOffset.y || glyphScreenCoords.right() < m_textVirtualOffset.x)
            continue;

        // bound glyph topLeft to startRenderPosition
        if(glyphScreenCoords.top() < m_textVirtualOffset.y) {
            glyphTextureCoords.setTop(glyphTextureCoords.top() + (m_textVirtualOffset.y - glyphScreenCoords.top()));
            glyphScreenCoords.setTop(m_textVirtualOffset.y);
        }
        if(glyphScreenCoords.left() < m_textVirtualOffset.x) {
            glyphTextureCoords.setLeft(glyphTextureCoords.left() + (m_textVirtualOffset.x - glyphScreenCoords.left()));
            glyphScreenCoords.setLeft(m_textVirtualOffset.x);
        }

        // subtract startInternalPos
        glyphScreenCoords.translate(-m_textVirtualOffset);

        // translate rect to screen coords
        glyphScreenCoords.translate(textScreenCoords.topLeft());

        // only render if glyph rect is visible on screenCoords
        if(!textScreenCoords.intersects(glyphScreenCoords))
            continue;

        // bound glyph bottomRight to screenCoords bottomRight
        if(glyphScreenCoords.bottom() > textScreenCoords.bottom()) {
            glyphTextureCoords.setBottom(glyphTextureCoords.bottom() + (textScreenCoords.bottom() - glyphScreenCoords.bottom()));
            glyphScreenCoords.setBottom(textScreenCoords.bottom());
        }
        if(glyphScreenCoords.right() > textScreenCoords.right()) {
            glyphTextureCoords.setRight(glyphTextureCoords.right() + (textScreenCoords.right() - glyphScreenCoords.right()));
            glyphScreenCoords.setRight(textScreenCoords.right());
        }

        // render glyph
        m_glyphsCoords[i] = glyphScreenCoords;
        m_glyphsTexCoords[i] = glyphTextureCoords;
    }

    if(fireAreaUpdate)
        onTextAreaUpdate(m_textVirtualOffset, m_textVirtualSize, m_textTotalSize);

    g_app.repaint();
}