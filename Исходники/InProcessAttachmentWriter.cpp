InProcessAttachmentWriter::InProcessAttachmentWriter(std::shared_ptr<SDSType> sds, SDSTypeWriter::Policy policy) {
    if (!sds) {
        ACSDK_ERROR(LX("constructorFailed").d("reason", "SDS parameter is nullptr"));
        return;
    }
    m_writer = sds->createWriter(policy);
}