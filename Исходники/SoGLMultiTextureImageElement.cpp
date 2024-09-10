/*!
  Sets the current texture. Id \a didapply is TRUE, it is assumed
  that the texture image already is the current GL texture. Do not
  use this feature unless you know what you're doing.
*/
void
SoGLMultiTextureImageElement::set(SoState * const state, SoNode * const node,
                                  const int unit,
                                  SoGLImage * image,
                                  Model model,
                                  const SbColor & blendColor)
{
  SoGLMultiTextureImageElement * elem = (SoGLMultiTextureImageElement*)
    state->getElement(classStackIndex);

  PRIVATE(elem)->ensureCapacity(unit);
  GLUnitData & ud = PRIVATE(elem)->unitdata[unit];
  
  // FIXME: buggy. Find some solution to handle this. pederb, 2003-11-12
  // if (ud.glimage && ud.glimage->getImage()) ud.glimage->getImage()->readUnlock();

  if (image) {
    // keep SoMultiTextureImageElement "up-to-date"
    inherited::set(state, node,
                   unit,
                   SbVec3s(0,0,0),
                   0,
                   NULL,
                   multi_translateWrap(image->getWrapS()),
                   multi_translateWrap(image->getWrapT()),
                   multi_translateWrap(image->getWrapR()),
                   model,
                   blendColor);
    ud.glimage = image;
    // make sure image isn't changed while this is the active texture
    // FIXME: buggy. Find some solution to handle this. pederb, 2003-11-12
    // if (image->getImage()) image->getImage()->readLock();
  }
  else {
    ud.glimage = NULL;
    inherited::setDefault(state, node, unit);
  }
  elem->updateGL(unit);

  // FIXME: check if it's possible to support for other units as well
  if ((unit == 0) && image && image->isOfType(SoGLBigImage::getClassTypeId())) {
    SoShapeStyleElement::setBigImageEnabled(state, TRUE);
  }
  SoShapeStyleElement::setTransparentTexture(state,
                                             SoGLMultiTextureImageElement::hasTransparency(state));
  
  SoGLShaderProgram * prog = SoGLShaderProgramElement::get(state);
  if (prog) {
    SbString str;
    str.sprintf("coin_texunit%d_model", unit);
    prog->updateCoinParameter(state, SbName(str.getString()), ud.glimage ? model : 0);
  }
}