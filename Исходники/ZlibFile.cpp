void ZlibFile::createDecompressedMemoryFile()
{
	MemoryFile * memoryFile = new MemoryFile(decompress(), m_uncompressedLength);
	close();
	m_decompressedMemoryFile = memoryFile;
}