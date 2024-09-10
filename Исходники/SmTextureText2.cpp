// doc from parent
void
SmTextureText2::GLRender(SoGLRenderAction * action)
{
  SoState * state = action->getState();
  
  const SbString * strings;
  const int numstrings = this->getStrings(state, strings);

  const SbVec3f * positions;
  const int numpositions = this->getPositions(state, positions);

  const float * rotations;
  const int numrotations = this->getRotations(state, rotations);

  const int32_t * indices;
  const int numindices = this->getStringIndices(state, indices);

  const int num = numindices > 0 ? numindices : numstrings;

  if ((numstrings == 0) || (numstrings == 1 && strings[0] == "") && numindices == 0) return;
  
  SbBool perpart =
    SoMaterialBindingElement::get(state) !=
    SoMaterialBindingElement::OVERALL;
  
  if (((numstrings == numpositions) || numindices > 0) &&
      SmTextureText2CollectorElement::isCollecting(state)) {
    SbMatrix modelmatrix = SoModelMatrixElement::get(state);
    const SbVec3f & offset = this->offset.getValue();
    SbVec3f pos;

    SbColor4f col(SoLazyElement::getDiffuse(state, 0),
                  1.0f - SoLazyElement::getTransparency(state, 0));
    
    for (int i = 0; i < num; i++) {
      const int idx = numindices > 0 ? indices[i] : i; 
      if (perpart) {
        col = SbColor4f(SoLazyElement::getDiffuse(state, idx),
                        1.0f - SoLazyElement::getTransparency(state, idx));
      }
      pos = positions[idx] + offset;
      modelmatrix.multVecMatrix(pos, pos);
      SmTextureText2CollectorElement::add(state,
                                          strings[idx],
                                          SmTextureFontElement::get(state),
                                          pos,
                                          this->maxRange.getValue(),
                                          col,
                                          static_cast<Justification>(this->justification.getValue()),
                                          static_cast<VerticalJustification>(this->verticalJustification.getValue()));
    }
    
    // invalidate caches to make sure this node is traversed every frame.
    SoCacheElement::invalidate(state);
    return;
  }
  
  SmTextureFontBundle bundle(action);
  SoCacheElement::invalidate(state);
  
  if (!this->shouldGLRender(action)) {
    return;
  }

  // set up my font texture
  SoLightModelElement::set(state, SoLightModelElement::BASE_COLOR);
  SoMaterialBundle mb(action);
  mb.sendFirst(); // make sure we have the correct material

  SbMatrix modelmatrix = SoModelMatrixElement::get(state);
  SbMatrix inv = modelmatrix.inverse();

  SbMatrix normalize(0.5f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.5f, 0.0f, 0.0f,
                     0.0f, 0.0f, 1.0f, 0.0f,
                     0.5f, 0.5f, 0.0f, 1.0f);
  SbMatrix projmatrix =
    modelmatrix *
    SoViewingMatrixElement::get(state) *
    SoProjectionMatrixElement::get(state) *
    normalize;

  const SbViewVolume & vv = SoViewVolumeElement::get(state);
  const SbViewportRegion & vp = SoViewportRegionElement::get(state);
  const SbVec2s vpsize = vp.getViewportSizePixels();
  const SbVec3f & offset = this->offset.getValue();

  SbVec3f tmp;

  // Set up new view volume
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho(0, vpsize[0], 0, vpsize[1], -1.0f, 1.0f);
  glPushAttrib(GL_DEPTH_BUFFER_BIT);
  glDepthFunc(GL_LEQUAL);

  if (numpositions > 1 || numindices > 0) {
    for (int i = 0; i < num; i++) {
      int idx = numindices > 0 ? indices[i] : i;
      float rotation = rotations[numrotations > 1 ? idx : 0];

      if (perpart) {
        mb.send(idx, FALSE);
      }
      tmp = positions[idx] + offset;
      this->renderString(bundle,
                         &strings[SbMin(idx, numstrings - 1)], 1,
                         tmp,
                         vv,
                         vp,
                         projmatrix,
                         modelmatrix,
                         inv,
                         rotation);
    }
  }
  else {
    tmp = numpositions > 0 ? positions[0] : SbVec3f(0.0f, 0.0f, 0.0f);
    tmp += offset;
    float rotation = rotations[0];
    this->renderString(bundle,
                       strings,
                       num,
                       tmp,
                       vv,
                       vp,
                       projmatrix,
                       modelmatrix,
                       inv,
                       rotation);
  }
  glPopAttrib();
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();

//#define DRAW_DEBUG_BBOXES
#ifdef DRAW_DEBUG_BBOXES
  glPushAttrib(GL_ALL_ATTRIB_BITS);
  glDisable(GL_TEXTURE_2D);
  glDepthFunc(GL_ALWAYS);
  for (int i = 0; i < num; i++){
    int idx = numindices > 0 ? indices[i] : i;
    SbVec3f p0, p1, p2, p3;
    this->buildStringQuad(action, idx, p0, p1, p2, p3);
    glBegin(GL_LINE_LOOP);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3fv((const GLfloat*)&p0);
    glVertex3fv((const GLfloat*)&p1);
    glVertex3fv((const GLfloat*)&p2);
    glVertex3fv((const GLfloat*)&p3);
    glEnd();
  }
  glPopAttrib();
#endif
}