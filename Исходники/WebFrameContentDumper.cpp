static void frameContentAsPlainText(size_t maxChars, LocalFrame* frame, StringBuilder& output)
{
    Document* document = frame->document();
    if (!document)
        return;

    if (!frame->view())
        return;

    // Select the document body.
    if (document->body()) {
        const EphemeralRange range = EphemeralRange::rangeOfContents(*document->body());

        // The text iterator will walk nodes giving us text. This is similar to
        // the plainText() function in core/editing/TextIterator.h, but we implement the maximum
        // size and also copy the results directly into a wstring, avoiding the
        // string conversion.
        for (TextIterator it(range.startPosition(), range.endPosition()); !it.atEnd(); it.advance()) {
            it.text().appendTextToStringBuilder(output, 0, maxChars - output.length());
            if (output.length() >= maxChars)
                return; // Filled up the buffer.
        }
    }

    // The separator between frames when the frames are converted to plain text.
    const LChar frameSeparator[] = { '\n', '\n' };
    const size_t frameSeparatorLength = WTF_ARRAY_LENGTH(frameSeparator);

    // Recursively walk the children.
    const FrameTree& frameTree = frame->tree();
    for (Frame* curChild = frameTree.firstChild(); curChild; curChild = curChild->tree().nextSibling()) {
        if (!curChild->isLocalFrame())
            continue;
        LocalFrame* curLocalChild = toLocalFrame(curChild);
        // Ignore the text of non-visible frames.
        LayoutView* contentLayoutObject = curLocalChild->contentLayoutObject();
        LayoutPart* ownerLayoutObject = curLocalChild->ownerLayoutObject();
        if (!contentLayoutObject || !contentLayoutObject->size().width() || !contentLayoutObject->size().height()
            || (contentLayoutObject->location().x() + contentLayoutObject->size().width() <= 0) || (contentLayoutObject->location().y() + contentLayoutObject->size().height() <= 0)
            || (ownerLayoutObject && ownerLayoutObject->style() && ownerLayoutObject->style()->visibility() != VISIBLE)) {
            continue;
        }

        // Make sure the frame separator won't fill up the buffer, and give up if
        // it will. The danger is if the separator will make the buffer longer than
        // maxChars. This will cause the computation above:
        //   maxChars - output->size()
        // to be a negative number which will crash when the subframe is added.
        if (output.length() >= maxChars - frameSeparatorLength)
            return;

        output.append(frameSeparator, frameSeparatorLength);
        frameContentAsPlainText(maxChars, curLocalChild, output);
        if (output.length() >= maxChars)
            return; // Filled up the buffer.
    }
}