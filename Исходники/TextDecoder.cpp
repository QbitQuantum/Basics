String TextDecoder::decode(ArrayBufferView* input, const Dictionary& options, ExceptionState& exceptionState)
{
    bool stream = false;
    options.get("stream", stream);

    const char* start = input ? static_cast<const char*>(input->baseAddress()) : 0;
    size_t length = input ? input->byteLength() : 0;

    WTF::FlushBehavior flush = stream ? WTF::DoNotFlush : WTF::DataEOF;

    bool sawError = false;
    String s = m_codec->decode(start, length, flush, m_fatal, sawError);

    if (m_fatal && sawError) {
        exceptionState.throwDOMException(EncodingError, "The encoded data was not valid.");
        return String();
    }

    if (!m_ignoreBOM && !m_bomSeen && !s.isEmpty()) {
        m_bomSeen = true;
        String name(m_encoding.name());
        if ((name == "UTF-8" || name == "UTF-16LE" || name == "UTF-16BE") && s[0] == 0xFEFF)
            s.remove(0);
    }

    if (flush)
        m_bomSeen = false;

    return s;
}