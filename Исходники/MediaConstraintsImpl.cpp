PassRefPtr<MediaConstraintsImpl> MediaConstraintsImpl::create(const Dictionary& constraints, ExceptionCode& ec)
{
    RefPtr<MediaConstraintsImpl> object = adoptRef(new MediaConstraintsImpl());
    if (!object->initialize(constraints)) {
        ec = TYPE_MISMATCH_ERR;
        return 0;
    }
    return object.release();
}