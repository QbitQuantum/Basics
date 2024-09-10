	void PrimitiveShape::paint()
	{
		VertexBuffer* vb = m_vertexbuffer;
		// IndexBuffer* ib = m_indexbuffer;
		Program* pr = m_program;
		if( !vb || !pr )
		{
			return;
		}
		size_t vertexcount;
		VertexDeclaration* vdecl;
		if( !vb->bind( &vertexcount, &vdecl ) )
		{
			return;
		}
		// int indexcount;
		// if( ib )
		// {
			// if( !ib->bind( &indexcount ) )
			// {
				// return;
			// }
		// }
		int worldmatrixpos;
		if( !pr->bind( &worldmatrixpos ) )
		{
			return;
		}
		int ptype = m_type.load( std::memory_order_acquire );
		glBlendEquation( m_blendop );
		checkerror();
		glBlendFunc( m_blendsf, m_blenddf );
		checkerror();
		if( worldmatrixpos != -1 )
		{
			lock_t lock( m_mutex );
			glUniformMatrix4fv( worldmatrixpos, 1, false, m_matrix );
		}
		// checkerror( Context::Device->DrawIndexedPrimitive(
			// D3DPRIMITIVETYPE( m_type ),
			// 0,
			// 0,
			// vertexcount,
			// 0,
			// indexcount / 3 ) );
		glDrawArrays( typetable[ ptype ], 0, GLsizei( vertexcount ) );
	}