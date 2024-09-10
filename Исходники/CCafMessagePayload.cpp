SmartPtrCDynamicByteArray CCafMessagePayload::createBufferFromStr(
		const std::string& payloadStr) {
	CAF_CM_STATIC_FUNC_VALIDATE("CCafMessagePayload", "createBufferFromStr");
	CAF_CM_VALIDATE_STRING(payloadStr);

	SmartPtrCDynamicByteArray rc;
	rc.CreateInstance();
	rc->allocateBytes(static_cast<uint32>(payloadStr.length()));
	rc->memCpy(payloadStr.c_str(), static_cast<uint32>(payloadStr.length()));

	return rc;
}