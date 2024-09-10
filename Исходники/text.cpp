void Text::UpdateText(bool onResize)
{
    rowWidths_.Clear();
    printText_.Clear();

    if (font_)
    {
        FontFace* face = font_->GetFace(fontSize_);
        if (!face)
            return;

        rowHeight_ = face->GetRowHeight();

        int width = 0;
        int height = 0;
        int rowWidth = 0;
        int rowHeight = (int)(rowSpacing_ * rowHeight_);

        // First see if the text must be split up
        if (!wordWrap_)
        {
            printText_ = unicodeText_;
            printToText_.Resize(printText_.Size());
            for (unsigned i = 0; i < printText_.Size(); ++i)
                printToText_[i] = i;
        }
        else
        {
            int maxWidth = GetWidth();
            unsigned nextBreak = 0;
            unsigned lineStart = 0;
            printToText_.Clear();

            for (unsigned i = 0; i < unicodeText_.Size(); ++i)
            {
                unsigned j;
                unsigned c = unicodeText_[i];

                if (c != '\n')
                {
                    bool ok = true;

                    if (nextBreak <= i)
                    {
                        int futureRowWidth = rowWidth;
                        for (j = i; j < unicodeText_.Size(); ++j)
                        {
                            unsigned d = unicodeText_[j];
                            if (d == ' ' || d == '\n')
                            {
                                nextBreak = j;
                                break;
                            }
                            const FontGlyph* glyph = face->GetGlyph(d);
                            if (glyph)
                            {
                                futureRowWidth += glyph->advanceX_;
                                if (j < unicodeText_.Size() - 1)
                                    futureRowWidth += face->GetKerning(d, unicodeText_[j + 1]);
                            }
                            if (d == '-' && futureRowWidth <= maxWidth)
                            {
                                nextBreak = j + 1;
                                break;
                            }
                            if (futureRowWidth > maxWidth)
                            {
                                ok = false;
                                break;
                            }
                        }
                    }

                    if (!ok)
                    {
                        // If did not find any breaks on the line, copy until j, or at least 1 char, to prevent infinite loop
                        if (nextBreak == lineStart)
                        {
                            while (i < j)
                            {
                                printText_.Push(unicodeText_[i]);
                                printToText_.Push(i);
                                ++i;
                            }
                        }
                        // Eliminate spaces that have been copied before the forced break
                        while (printText_.Size() && printText_.Back() == ' ')
                        {
                            printText_.Pop();
                            printToText_.Pop();
                        }
                        printText_.Push('\n');
                        printToText_.Push((unsigned)Min((int)i, (int)unicodeText_.Size() - 1));
                        rowWidth = 0;
                        nextBreak = lineStart = i;
                    }

                    if (i < unicodeText_.Size())
                    {
                        // When copying a space, position is allowed to be over row width
                        c = unicodeText_[i];
                        const FontGlyph* glyph = face->GetGlyph(c);
                        if (glyph)
                        {
                            rowWidth += glyph->advanceX_;
                            if (i < unicodeText_.Size() - 1)
                                rowWidth += face->GetKerning(c, unicodeText_[i + 1]);
                        }
                        if (rowWidth <= maxWidth)
                        {
                            printText_.Push(c);
                            printToText_.Push(i);
                        }
                    }
                }
                else
                {
                    printText_.Push('\n');
                    printToText_.Push((unsigned)Min((int)i, (int)unicodeText_.Size() - 1));
                    rowWidth = 0;
                    nextBreak = lineStart = i;
                }
            }
        }

        rowWidth = 0;

        for (unsigned i = 0; i < printText_.Size(); ++i)
        {
            unsigned c = printText_[i];

            if (c != '\n')
            {
                const FontGlyph* glyph = face->GetGlyph(c);
                if (glyph)
                {
                    rowWidth += glyph->advanceX_;
                    if (i < printText_.Size() - 1)
                        rowWidth += face->GetKerning(c, printText_[i + 1]);
                }
            }
            else
            {
                width = Max(width, rowWidth);
                height += rowHeight;
                rowWidths_.Push(rowWidth);
                rowWidth = 0;
            }
        }

        if (rowWidth)
        {
            width = Max(width, rowWidth);
            height += rowHeight;
            rowWidths_.Push(rowWidth);
        }

        // Set at least one row height even if text is empty
        if (!height)
            height = rowHeight;

        // Set minimum and current size according to the text size, but respect fixed width if set
        if (!IsFixedWidth())
        {
            SetMinWidth(wordWrap_ ? 0 : width);
            SetWidth(width);
        }
        SetFixedHeight(height);

        charLocationsDirty_ = true;
    }
    else
    {
        // No font, nothing to render
        pageGlyphLocations_.Clear();
    }

    // If wordwrap is on, parent may need layout update to correct for overshoot in size. However, do not do this when the
    // update is a response to resize, as that could cause infinite recursion
    if (wordWrap_ && !onResize)
    {
        UIElement* parent = GetParent();
        if (parent && parent->GetLayoutMode() != LM_FREE)
            parent->UpdateLayout();
    }
}