PassRefPtr<RTCOfferOptions> RTCOfferOptions::create(const Dictionary& options, ExceptionCode& ec)
{
    RefPtr<RTCOfferOptions> offerOptions = adoptRef(new RTCOfferOptions());
    if (!offerOptions->initialize(options)) {
        // FIXME: https://webkit.org/b/129800
        // According to the spec, the error is going to be defined yet, so let's use TYPE_MISMATCH_ERR for now.
        ec = TYPE_MISMATCH_ERR;
        return nullptr;
    }

    return offerOptions.release();
}