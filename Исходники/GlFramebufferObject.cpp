void GlRenderbufferObject::createObject(GLint internalFormat,
                                        GLsizei width, GLsizei height) {
  deleteObject();
  glGenRenderbuffersEXT(1, &_handle);
  glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, _handle);
  glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, internalFormat, width, height);
}