static void frameContentAsPlainText(size_t maxChars, LocalFrame* frame, StringBuilder& output)
{
    Document* document = frame->document();
    if (!document)
        return;

    if (!frame->view())
        return;

    // Select the document body.
    RefPtr<Range> range(document->createRange());
    TrackExceptionState exceptionState;
    range->selectNodeContents(document, exceptionState);

    if (!exceptionState.had_exception()) {
        // The text iterator will walk nodes giving us text. This is similar to
        // the plainText() function in core/editing/TextIterator.h, but we implement the maximum
        // size and also copy the results directly into a wstring, avoiding the
        // string conversion.
        for (TextIterator it(range.get()); !it.atEnd(); it.advance()) {
            it.appendTextToStringBuilder(output, 0, maxChars - output.length());
            if (output.length() >= maxChars)
                return; // Filled up the buffer.
        }
    }
}