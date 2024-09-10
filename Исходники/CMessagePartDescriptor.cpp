/**
 * Converts the BLOCK_SIZE data in a ByteBuffer into a MessagePartsDescriptor
 * <p>
 * The incoming ByteBuffer position will be modified.
 * @param buffer ByteBuffer to convert
 * @return a MessagePartsDescriptor
 */
SmartPtrCMessagePartDescriptor CMessagePartDescriptor::fromByteBuffer(
	SmartPtrCDynamicByteArray& buffer) {
	CAF_CM_STATIC_FUNC("CMessagePartDescriptor", "fromByteBuffer");
	CAF_CM_VALIDATE_SMARTPTR(buffer);

	if (buffer->getByteCountFromCurrentPos() < BLOCK_SIZE) {
		CAF_CM_EXCEPTION_VA2(E_INVALIDARG,
			"Input data block is too small - rem: %d, tot: %d",
			buffer->getByteCountFromCurrentPos(), buffer->getByteCount());
	}

	SmartPtrCDynamicByteArray data;
	data.CreateInstance();
	data->allocateBytes(BLOCK_SIZE);
	data->memCpy(buffer->getPtrAtCurrentPos(), BLOCK_SIZE);

	buffer->incrementCurrentPos(BLOCK_SIZE);
	return fromArray(data);
}