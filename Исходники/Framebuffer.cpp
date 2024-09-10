	void	cScreenCapture::Render(Vector3 e_vPos,int e_iWidth,int e_iHeight)
	{
		if( m_uiWidth == -1 )
			return;
		glBindTexture( GL_TEXTURE_2D, m_uiTextureID);
		e_iWidth /= 2;
		e_iHeight /= 2;

		float	l_fTexPointer[] = {  0,1,
									 1,1,
									 0,0,
									 1,0};
		
		float	l_Vertices[] = { (float)-e_iWidth,(float)-e_iHeight,0,
								 (float)e_iWidth, (float)-e_iHeight,0,
								 (float)-e_iWidth, (float)e_iHeight,0,
								 (float)e_iWidth,(float)e_iHeight,0};

		cMatrix44	l_mat = cMatrix44::TranslationMatrix(Vector3((float)(e_vPos.x+e_iWidth),(float)(e_vPos.y+e_iHeight), e_vPos.z));
		SetupShaderWorldMatrix(l_mat*GetWorldTransform());
		myGlVertexPointer(3,l_Vertices);
		myGlUVPointer(2,l_fTexPointer);
		ASSIGN_2D_COLOR(Vector4::One);
		MY_GLDRAW_ARRAYS(GL_TRIANGLE_STRIP, 0, 4);

	}