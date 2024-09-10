void glTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid * pixels)
{
	bool is_set = false;
	
#ifdef _DEBUG
	return;
#endif

#if 1 // no mipmap
	if (level > 0)
		return;
#endif

	if (!GLImpl.tmus[GLImpl.current_tmu].boundtexture) {
		printf("Not texture binded\n");
		return;
	}
		
	GLImpl.device->SetTexture(0, NULL);
	GLTexture * surf = NULL;
	
	if (GLImpl.tmus[GLImpl.current_tmu].boundtexture && GLImpl.tmus[GLImpl.current_tmu].boundtexture->teximg ) {
		surf = GLImpl.tmus[GLImpl.current_tmu].boundtexture->teximg;
	}
	
	if (surf) {
		int srcbytes = src_format_to_bypp(format);
		int dstbytes = dst_format_to_bypp(GLImpl.tmus[GLImpl.current_tmu].boundtexture->internalformat);
		BYTE * surfbuf;
		BYTE * srcdata = (BYTE*) pixels;
		BYTE * dstdata;

		surf->lockTexture(level);

		srcdata = (BYTE*) pixels;
		surfbuf = (BYTE*)surf->getData();		
		dstdata = (BYTE*)surf->getData();
		
		check_format(srcbytes, dstbytes);

		copyImage(xoffset, yoffset, width, height, srcdata, srcbytes, surfbuf, dstbytes);

		surf->unlockTexture(level);

		GLImpl.tmus[GLImpl.current_tmu].boundtexture->dirty = 1;
	}
}