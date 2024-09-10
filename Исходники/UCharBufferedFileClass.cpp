void pelet::UCharBufferedFileClass::GrowBuffer(int minCapacity) {
	int newCapacity = minCapacity < (2 * BufferCapacity) ? (2 * BufferCapacity) : minCapacity;
	UChar* newBuffer = new UChar[newCapacity];
	u_memcpy(newBuffer, Buffer, BufferCapacity);
	u_memset(newBuffer + BufferCapacity, 'i', newCapacity / 2);
	
	
	// change all of the pointers
	TokenStart = newBuffer + (TokenStart - Buffer);
	Current = newBuffer + (Current - Buffer);
	
	// leave Limit at the place where the last good character is located
	Limit = newBuffer + (Limit - Buffer);
	Marker = newBuffer + (Marker - Buffer);
	
	delete[] Buffer;
	Buffer = newBuffer;
	BufferCapacity = newCapacity;
}