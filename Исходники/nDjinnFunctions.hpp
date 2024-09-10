inline void frontFace(GLenum const mode)
{
  glFrontFace(mode);
  checkError("glFrontFace");
}