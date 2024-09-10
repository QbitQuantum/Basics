 /// Binds as image.
 ///
 /// Without redundancy checking! Does not perform checks if texture format is valid (see http://docs.gl/gl4/glBindImageTexture)!
 /// (TODO)
 void BindImage(GLuint _slotIndex, ImageAccess _access, GLint _level = 0) const {
     BindImage(_slotIndex, _access, m_format, _level);
 }