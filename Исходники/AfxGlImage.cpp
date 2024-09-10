void * AfxGlImage::SetFormat(GLsizei  width,  GLsizei  height,  GLenum  format,  GLenum  type)
{
	unsigned char numComponents;

	if (!_CalcNumComponents(format, &numComponents))
		return 0;

	unsigned char sizeComponent;
	bool componentSigned;

	if (!_CalcSizeComponent(type, &sizeComponent, &componentSigned))
		return 0;

	size_t pixelSize = (size_t)numComponents * (size_t)sizeComponent;
	size_t rowSize = width * pixelSize;

	// assuming GL_PIXEL_ALIGNMENT == 4:
	if (rowSize & 0x03)
		// is not divideable by 4 (has remainder)
		rowSize = (1+ (rowSize >> 2))<<2; // fill up to 4

	size_t imageSize = height * rowSize;

	void * newMemory = Realloc(imageSize);

	if(!newMemory)
		return 0;

	m_Format = format;
	m_Height = height;
	m_Pitch = rowSize;
	m_Type = type;
	m_Width = width;

	return newMemory;
}