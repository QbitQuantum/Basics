/** 
 * Unlocks the buffer.  Pointers to buffer data will no longer be valid after this call
 */
void FSlateOpenGLIndexBuffer::Unlock()
{
	Bind();
	glUnmapBuffer( GL_ELEMENT_ARRAY_BUFFER );
}