void create_spherical_texture(int size, GLuint& tex)
{
	struct elem {
		unsigned char l;
		unsigned char a;
	};

	elem* buffer = (elem *) malloc(size * size * sizeof(elem));
	float r = (float)size / 2.0;

	for(int i = 0; i < size; ++i)
	{
		for(int j = 0; j < size; ++j)
		{
			float d = hypotf(i - r, j - r);
			buffer[(i * size) + j].l = 255u;
			buffer[(i * size) + j].a = d > r ? 0u : (unsigned char)nearbyint(sqrtf(r*r - d*d) / r * 255.0);
		}
	}

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE_ALPHA, size, size, 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, (GLvoid*)buffer);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	free(buffer);
}