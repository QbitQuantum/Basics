void VertexBufferObject::Draw(int offset) const
{
	Bind();
	glDrawArrays(GL_TRIANGLES, offset, vertexCount);
	Unbind();
}