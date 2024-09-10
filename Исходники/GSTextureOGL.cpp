GSTextureOGL::GSTextureOGL(int type, int w, int h, int format, GLuint fbo_read)
	: m_pbo_size(0), m_clean(false), m_local_buffer(NULL), m_r_x(0), m_r_y(0), m_r_w(0), m_r_h(0)
{
	// OpenGL didn't like dimensions of size 0
	m_size.x = max(1,w);
	m_size.y = max(1,h);
	m_format = format;
	m_type   = type;
	m_fbo_read = fbo_read;
	m_texture_id = 0;

	// Bunch of constant parameter
	switch (m_format) {
			// 1 Channel integer
		case GL_R32UI:
		case GL_R32I:
			m_int_format    = GL_RED_INTEGER;
			m_int_type      = (m_format == GL_R32UI) ? GL_UNSIGNED_INT : GL_INT;
			m_int_shift     = 2;
			break;
		case GL_R16UI:
			m_int_format    = GL_RED_INTEGER;
			m_int_type      = GL_UNSIGNED_SHORT;
			m_int_shift     = 1;
			break;

			// 1 Channel normalized
		case GL_R8:
			m_int_format    = GL_RED;
			m_int_type      = GL_UNSIGNED_BYTE;
			m_int_shift     = 0;
			break;

			// 4 channel normalized
		case GL_RGBA16:
			m_int_format    = GL_RGBA;
			m_int_type      = GL_UNSIGNED_SHORT;
			m_int_shift     = 3;
			break;
		case GL_RGBA8:
			m_int_format    = GL_RGBA;
			m_int_type      = GL_UNSIGNED_BYTE;
			m_int_shift     = 2;
			break;

			// 4 channel integer
		case GL_RGBA16I:
		case GL_RGBA16UI:
			m_int_format    = GL_RGBA_INTEGER;
			m_int_type      = (m_format == GL_R16UI) ? GL_UNSIGNED_SHORT : GL_SHORT;
			m_int_shift     = 3;
			break;

			// 4 channel float
		case GL_RGBA32F:
			m_int_format    = GL_RGBA;
			m_int_type      = GL_FLOAT;
			m_int_shift     = 4;
			break;
		case GL_RGBA16F:
			m_int_format    = GL_RGBA;
			m_int_type      = GL_HALF_FLOAT;
			m_int_shift     = 3;
			break;

			// Depth buffer
		case GL_DEPTH32F_STENCIL8:
			m_int_format    = GL_DEPTH_STENCIL;
			m_int_type      = GL_FLOAT_32_UNSIGNED_INT_24_8_REV;
			m_int_shift     = 0;
			break;

			// Backbuffer
		case 0:
			m_int_format    = 0;
			m_int_type      = 0;
			m_int_shift     = 0;
			break;

		default:
			m_int_format    = 0;
			m_int_type      = 0;
			m_int_shift     = 0;
			ASSERT(0);
	}

	// Generate & Allocate the buffer
	switch (m_type) {
		case GSTexture::Offscreen:
			// Offscreen is only used to read color. So it only requires 4B by pixel
			m_local_buffer = (uint8*)_aligned_malloc(m_size.x * m_size.y * 4, 32);
		case GSTexture::Texture:
		case GSTexture::RenderTarget:
		case GSTexture::DepthStencil:
			glCreateTextures(GL_TEXTURE_2D, 1, &m_texture_id);
			glTextureStorage2D(m_texture_id, 1+GL_TEX_LEVEL_0, m_format, m_size.x, m_size.y);
			if (m_format == GL_R8) {
				// Emulate DX behavior, beside it avoid special code in shader to differentiate
				// palette texture from a GL_RGBA target or a GL_R texture.
				glTextureParameteri(m_texture_id, GL_TEXTURE_SWIZZLE_A, GL_RED);
			}
			break;
		case GSTexture::Backbuffer:
		default:
			break;
	}
}