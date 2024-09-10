SafeVector<uint8_t> ProtectedBuffer::toBuffer(){
	SafeVector<uint8_t> result(data.begin(), data.end());
	decrypt(result.data(), result.size());
	return result;
}