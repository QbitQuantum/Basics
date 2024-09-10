SkStream* FontConfigTypeface::onOpenStream(int* ttcIndex) const {
    SkStream* stream = this->getLocalStream();
    if (stream) {
        // TODO: fix issue 1176.
        // As of now open_stream will return a stream and unwind it, but the
        // SkStream is not thread safe, and if two threads use the stream they
        // may collide and print preview for example could still fail,
        // or there could be some failures in rendering if this stream is used
        // there.
        stream->rewind();
        stream->ref();
        // should have been provided by CreateFromStream()
        *ttcIndex = 0;
    } else {
        SkAutoTUnref<SkFontConfigInterface> fci(RefFCI());
        if (NULL == fci.get()) {
            return NULL;
        }
        stream = fci->openStream(this->getIdentity());
        *ttcIndex = this->getIdentity().fTTCIndex;
    }
    return stream;
}