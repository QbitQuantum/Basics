	bool VertexBuffer::bind( size_t* vertexcount, VertexDeclaration** pvd )
	{
		VertexDeclaration* vd = m_vertexdeclaration;
		if( !vd || !m_vertexbuffer )
		{
			return false;
		}
		if( Context::CurrentVertexBuffer != this )
		{
			glBindBuffer( GL_ARRAY_BUFFER, m_vertexbuffer );
			checkerror();
			Context::CurrentVertexBuffer = this;
		}
		size_t vertexsize;
		if( !vd->bind( &vertexsize ) )
		{
			return false;
		}
		*vertexcount = m_buffersize / vertexsize;
		*pvd = vd;
		return true;
	}