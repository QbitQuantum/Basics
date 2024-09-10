void StyledMarkupAccumulator::appendText(StringBuilder& out, Text* text)
{    
    const bool parentIsTextarea = text->parentElement() && text->parentElement()->tagQName() == textareaTag;
    const bool wrappingSpan = shouldApplyWrappingStyle(text) && !parentIsTextarea;
    if (wrappingSpan) {
        RefPtr<EditingStyle> wrappingStyle = m_wrappingStyle->copy();
        // FIXME: <rdar://problem/5371536> Style rules that match pasted content can change it's appearance
        // Make sure spans are inline style in paste side e.g. span { display: block }.
        wrappingStyle->forceInline();
        // FIXME: Should this be included in forceInline?
        wrappingStyle->style()->setProperty(CSSPropertyFloat, CSSValueNone);

        StringBuilder openTag;
        appendStyleNodeOpenTag(openTag, wrappingStyle->style(), text->document());
        out.append(openTag.characters(), openTag.length());
    }

    if (!shouldAnnotate() || parentIsTextarea)
        MarkupAccumulator::appendText(out, text);
    else {
        const bool useRenderedText = !enclosingNodeWithTag(firstPositionInNode(text), selectTag);
        String content = useRenderedText ? renderedText(text, m_range) : stringValueForRange(text, m_range);
        StringBuilder buffer;
        appendCharactersReplacingEntities(buffer, content.characters(), content.length(), EntityMaskInPCDATA);
        out.append(convertHTMLTextToInterchangeFormat(buffer.toString(), text));
    }

    if (wrappingSpan)
        out.append(styleNodeCloseTag());
}