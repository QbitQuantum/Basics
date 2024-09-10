static EF_Error ef_internal_video_load_texture_gd_image(gdImage *image,
							GLuint id,
							int build_mipmaps)
{
    GLint pixel_format;
    GLint component_format;
    GLsizei size;
    uint8_t *data;
    
    int width = gdImageSX(image);
    int height = gdImageSY(image);
    int widthLog2 = ceil(log2(width));
    int heightLog2 = ceil(log2(height));
    int sizeLog2 = widthLog2 > heightLog2 ? widthLog2 : heightLog2;
    size = 1;
    for(int i = 0; i < sizeLog2; i++)
	size *= 2;
    
    pixel_format = GL_RGBA;
    
    component_format = GL_UNSIGNED_BYTE;
    
    data = malloc(size*size*4);
    for(int y = 0; y < size; y++) {
	for(int x = 0; x < size; x++) {
	    if((y < height) && (x < width)) {
		int color = gdImageGetPixel(image, x, y);
		data[(x + y*size)*4] = gdImageRed(image, color);
		data[(x + y*size)*4+1] = gdImageGreen(image, color);
		data[(x + y*size)*4+2] = gdImageBlue(image, color);
		int alpha = (127 - gdImageAlpha(image, color)) * 2;
		data[(x + y*size)*4+3] = alpha;
	    } else {
		data[(x + y*size)*4] = 0x00;
		data[(x + y*size)*4+1] = 0x00;
		data[(x + y*size)*4+2] = 0x00;
		data[(x + y*size)*4+3] = 0x00;
	    }
	}
    }
    
    glBindTexture(GL_TEXTURE_2D, id);
    
    glPixelStorei(GL_UNPACK_ROW_LENGTH, size);
    glPixelStorei(GL_UNPACK_IMAGE_HEIGHT, size);
    
    if(build_mipmaps) {
	gluBuild2DMipmaps(GL_TEXTURE_2D,
			  pixel_format,
			  size, size,
			  pixel_format,
			  component_format,
			  data);
    } else {
	glTexImage2D(GL_TEXTURE_2D,
		     0,
		     pixel_format,
		     size, size,
		     0,
		     pixel_format,
		     component_format,
		     data);
    }
    
    free(data);

    glBindTexture(GL_TEXTURE_2D, 0);
}